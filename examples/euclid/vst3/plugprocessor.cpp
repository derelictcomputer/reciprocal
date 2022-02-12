#include <memory>
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "plugprocessor.h"
#include "plugids.h"

using namespace Steinberg;

namespace dc::euclid {
PlugProcessor::PlugProcessor() : _euclid(rateMin, rateMax, rateDef, rateStep, stepsDef, pulsesDef)
{
	setControllerClass(EuclidControllerId);
}


tresult PLUGIN_API PlugProcessor::initialize (FUnknown* context)
{
	tresult result = AudioEffect::initialize (context);
	if (result != kResultTrue) {
    return kResultFalse;
  }

  addAudioInput(STR16("AudioInput"), Vst::SpeakerArr::kStereo);
  addAudioOutput(STR16("AudioOutput"), Vst::SpeakerArr::kStereo);

  addEventInput(STR16("EventIn"), 16);
  addEventOutput(STR16("EventOut"), 16);

	return kResultTrue;
}

tresult PLUGIN_API PlugProcessor::setBusArrangements (Vst::SpeakerArrangement* inputs,
                                                            int32 numIns,
                                                            Vst::SpeakerArrangement* outputs,
                                                            int32 numOuts)
{
	if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
	{
		return AudioEffect::setBusArrangements (inputs, numIns, outputs, numOuts);
	}
	return kResultFalse;
}

tresult PLUGIN_API PlugProcessor::setupProcessing (Vst::ProcessSetup& setup)
{
	return AudioEffect::setupProcessing(setup);
}

tresult PLUGIN_API PlugProcessor::setActive (TBool state)
{
	return AudioEffect::setActive (state);
}

tresult PLUGIN_API PlugProcessor::process(Vst::ProcessData& data) {
  // Param changes
  if (data.inputParameterChanges) {
    int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
    for (int32 index = 0; index < numParamsChanged; index++) {
      Vst::IParamValueQueue* paramQueue =
          data.inputParameterChanges->getParameterData(index);
      if (paramQueue) {
        int32 numPoints = paramQueue->getPointCount();
        Vst::ParamValue valueNormalized;
        int32 sampleOffset;
        if (paramQueue->getPoint(numPoints - 1, sampleOffset, valueNormalized) == kResultTrue) {
          const auto paramIdx = paramQueue->getParameterId();
          const auto param = static_cast<ParamId>(paramIdx);
          switch (param) {
            case ParamId::Enable: {
              const auto status = _euclid.setEnabled(valueNormalized > 0.5);
              if (status != Status::Ok) {
                return kResultFalse;
              }
              break;
            }
            case ParamId::Rate: {
              auto valueScaled = (rateMax - rateMin) * valueNormalized;
              if (rateStep > 0) {
                valueScaled = rateMin + rateStep * std::floor(valueScaled / rateStep + 0.5);
              }
              const auto status = _euclid.setRate(valueScaled);
              if (status != Status::Ok) {
                return kResultFalse;
              }
              break;
            }
            case ParamId::Pulses: {
              auto valueScaled = static_cast<uint8_t>(stepsMin + (stepsMax - stepsMin) * valueNormalized);
              const auto status = _euclid.setPulses(valueScaled);
              if (status != Status::Ok) {
                return kResultFalse;
              }
              break;
            }
            case ParamId::Steps: {
              auto valueScaled = static_cast<uint8_t>(stepsMin + (stepsMax - stepsMin) * valueNormalized);
              const auto status = _euclid.setSteps(valueScaled);
              if (status != Status::Ok) {
                return kResultFalse;
              }
              break;
            }
          }
        }
      }
    }
  }

  // process
  if (data.processContext != nullptr) {
    const bool isPlaying = (data.processContext->state & Steinberg::Vst::ProcessContext::kPlaying) != 0;
    if (isPlaying) {
      const bool musicTimeValid =
          (data.processContext->state & Steinberg::Vst::ProcessContext::kProjectTimeMusicValid) != 0;
      if (musicTimeValid) {
        const auto posQuarterNotes = data.processContext->projectTimeMusic;
        if (!_wasPlaying) {
          _lastTimeQuarters = posQuarterNotes;
          _wasPlaying = isPlaying;
        }
        const auto status = _euclid.process(posQuarterNotes - _lastTimeQuarters);
        if (status != Status::Ok) {
          return kResultFalse;
        }
        Vst::IEventList* outputEvents = data.outputEvents;
        assert(outputEvents != nullptr);
        Message<Euclid<double>::DataType, double> msg;
        while (_euclid.popOutputMessage(msg) == Status::Ok) {
          {
            Vst::Event e{};
            e.busIndex = 0;
            e.sampleOffset = 0;
            e.ppqPosition = msg.time;
            e.flags = 0;
            e.type = Vst::Event::EventTypes::kNoteOnEvent;
            e.noteOn.channel = 0;
            e.noteOn.pitch = 60;
            e.noteOn.noteId = 60;
            e.noteOn.tuning = 0;
            e.noteOn.velocity = 1.0;
            e.noteOn.length = 0;
            outputEvents->addEvent(e);
          }
          {
            Vst::Event e{};
            e.busIndex = 0;
            e.sampleOffset = 1;
            e.ppqPosition = msg.time;
            e.flags = 0;
            e.type = Vst::Event::EventTypes::kNoteOffEvent;
            e.noteOff.channel = 0;
            e.noteOff.pitch = 60;
            e.noteOff.noteId = 60;
            e.noteOff.tuning = 0;
            e.noteOff.velocity = 1.0;
            outputEvents->addEvent(e);
          }
        }
      }
    }
  }

  // Pass through audio
  if (data.numInputs == 0 || data.numOutputs == 0) {
    return kResultOk;
  }

  if (data.inputs[0].numChannels != data.outputs[0].numChannels) {
    return kResultFalse;
  }

  // pass through audio
  int32 numChannels = data.inputs[0].numChannels;
  float** in = data.inputs[0].channelBuffers32;
  float** out = data.outputs[0].channelBuffers32;
  for (int32 i = 0; i < numChannels; i++) {
    if (in[i] != out[i]) {
      memcpy(out[i], in[i], data.numSamples * sizeof(float));
    }
  }

  return kResultOk;
}

tresult PLUGIN_API PlugProcessor::setState (IBStream* state)
{
	if (!state)
		return kResultFalse;

	IBStreamer streamer (state, kLittleEndian);
  bool enabled;
  if (!streamer.readBool(enabled)) {
    return kResultFalse;
  }
  auto status = _euclid.setEnabled(enabled);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  double rate;
  if (!streamer.readDouble(rate)) {
    return kResultFalse;
  }
  status = _euclid.setRate(rate);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  uint8_t pulses;
  if (!streamer.readUChar8(pulses)) {
    return kResultFalse;
  }
  status = _euclid.setPulses(pulses);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  uint8_t steps;
  if (!streamer.readUChar8(steps)) {
    return kResultFalse;
  }
  status = _euclid.setSteps(steps);
  if (status != Status::Ok) {
    return kResultFalse;
  }

	return kResultOk;
}

tresult PLUGIN_API PlugProcessor::getState (IBStream* state)
{
  IBStreamer streamer (state, kLittleEndian);
  bool enabled;
  auto status = _euclid.getEnabled(enabled);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  if (!streamer.writeBool(enabled)) {
    return kResultFalse;
  }
  double rate;
  status = _euclid.getRate(rate);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  if (!streamer.writeDouble(rate)) {
    return kResultFalse;
  }
  uint8_t pulses;
  status = _euclid.getPulses(pulses);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  if (!streamer.writeUChar8(pulses)) {
    return kResultFalse;
  }
  uint8_t steps;
  status = _euclid.getSteps(steps);
  if (status != Status::Ok) {
    return kResultFalse;
  }
  if (!streamer.writeUChar8(steps)) {
    return kResultFalse;
  }

  return kResultOk;
}

uint32 PlugProcessor::getProcessContextRequirements() {
  processContextRequirements.needProjectTimeMusic();
  processContextRequirements.needTransportState();
  return AudioEffect::getProcessContextRequirements();
}
}
