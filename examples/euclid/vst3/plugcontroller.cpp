#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "plugcontroller.h"
#include "plugids.h"
#include "pluginterfaces/base/ustring.h"

using namespace Steinberg;

namespace dc::euclid {
tresult PLUGIN_API PlugController::initialize (FUnknown* context) {
  tresult result = EditController::initialize(context);
  if (result == kResultTrue) {
    parameters.addParameter(USTRING("Enabled"),
                            nullptr,
                            1,
                            0,
                            Vst::ParameterInfo::kCanAutomate,
                            (Vst::ParamID) ParamId::Enable,
                            0,
                            nullptr);
    parameters.addParameter(new Vst::RangeParameter(USTRING("Rate"),
                                                    (Vst::ParamID) ParamId::Rate,
                                                    nullptr,
                                                    rateMin,
                                                    rateMax,
                                                    rateDef,
                                                    0,
                                                    Vst::ParameterInfo::kCanAutomate,
                                                    0,
                                                    nullptr));
    parameters.addParameter(new Vst::RangeParameter(USTRING("Pulses"),
                                                    (Vst::ParamID) ParamId::Pulses,
                                                    nullptr,
                                                    stepsMin,
                                                    stepsMax,
                                                    pulsesDef,
                                                    (int32) (stepsMax - stepsMin),
                                                    Vst::ParameterInfo::kCanAutomate,
                                                    0,
                                                    nullptr));
    parameters.addParameter(new Vst::RangeParameter(USTRING("Steps"),
                                                    (Vst::ParamID) ParamId::Steps,
                                                    nullptr,
                                                    stepsMin,
                                                    stepsMax,
                                                    stepsDef,
                                                    (int32) (stepsMax - stepsMin),
                                                    Vst::ParameterInfo::kCanAutomate,
                                                    0,
                                                    nullptr));
  }
  return result;
}

tresult PLUGIN_API PlugController::setComponentState (IBStream* state)
{
  if (!state)
    return kResultFalse;

  IBStreamer streamer (state, kLittleEndian);
  bool enabled;
  if (!streamer.readBool(enabled)) {
    return kResultFalse;
  }
  setParamNormalized((Vst::ParamID)ParamId::Enable, enabled);
  double rate;
  if (!streamer.readDouble(rate)) {
    return kResultFalse;
  }
  auto norm = (rate - rateMin) / (rateMax - rateMin);
  setParamNormalized((Vst::ParamID)ParamId::Rate, norm);
  uint8_t pulses;
  if (!streamer.readUChar8(pulses)) {
    return kResultFalse;
  }
  norm = (double)(pulses - stepsMin) / (stepsMax - stepsMin);
  setParamNormalized((Vst::ParamID)ParamId::Pulses, norm);
  uint8_t steps;
  if (!streamer.readUChar8(steps)) {
    return kResultFalse;
  }
  norm = (double)(steps - stepsMin) / (stepsMax - stepsMin);
  setParamNormalized((Vst::ParamID)ParamId::Steps, norm);

	return kResultOk;
}
}
