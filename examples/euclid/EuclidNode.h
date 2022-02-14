#pragma once

#include "dagnabbit/Node.h"
#include "dagnabbit/Param.h"

namespace dc::euclid {
template<class TimeType, class DataType>
class EuclidNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;
  using InputType = InputPort<MessageType>;
  using OutputType = OutputPort<MessageType>;

  explicit EuclidNode(const Param<uint8_t>& pulsesParam,
                      const Param<uint8_t>& stepsParam,
                      size_t queueSize,
                      size_t maxOutputConnections) :
      _pulses(pulsesParam),
      _steps(stepsParam),
      _in(this, "in", queueSize),
      _out(this, "out", maxOutputConnections) {
    this->_inputs.push_back(&_in);
    this->_outputs.push_back(&_out);
  }

  [[nodiscard]] uint8_t getSteps() const {
    return _steps.get();
  }

  [[nodiscard]] double getStepsNormalized() const {
    return _steps.getNormalized();
  }

  void setSteps(uint8_t steps) {
    if (_pulses.get() > steps) {
      _pulses.set(steps);
    }
    _steps.set(steps);
  }

  void setStepsNormalized(double normalized) {
    if (_pulses.getNormalized() > normalized) {
      _pulses.setNormalized(normalized);
    }
    _steps.setNormalized(normalized);
  }

  [[nodiscard]] uint8_t getPulses() const {
    return _pulses.get();
  }

  [[nodiscard]] double getPulsesNormalized() const {
    return _pulses.getNormalized();
  }

  void setPulses(uint8_t pulses) {
    if (pulses > _steps.get()) {
      return;
    }
    _pulses.set(pulses);
  }

  void setPulsesNormlized(double normalized) {
    if (normalized > _steps.getNormalized()) {
      return;
    }
    _pulses.setNormalized(normalized);
  }

  Status process(const TimeType&, const TimeType&) override {
    const auto steps = _steps.get();
    const auto pulses = _pulses.get();
    MessageType msg;
    while (_in.popMessage(msg) == Status::Ok) {
      if (stepIsOn(_currentStep % steps, steps, pulses)) {
        const auto status = _out.pushToConnections(msg);
        if (status != Status::Ok) {
          return status;
        }
      }
      ++_currentStep;
    }

    return Status::Ok;
  }

private:
  static bool stepIsOn(uint8_t step, uint8_t numSteps, uint8_t numPulses) {
    return (step * numPulses) % numSteps < numPulses;
  }

  Param<uint8_t> _pulses;
  Param<uint8_t> _steps;
  InputType _in;
  OutputType _out;
  size_t _currentStep{0};
};
}
