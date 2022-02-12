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

  explicit EuclidNode(uint8_t defaultSteps, uint8_t defaultPulses, size_t queueSize, size_t maxOutputConnections) :
      _steps(1, 16, defaultSteps, 1),
      _pulses(1, 16, defaultPulses <= defaultSteps ? defaultPulses : defaultSteps, 1),
      _in(this, "in", queueSize),
      _out(this, "out", maxOutputConnections) {
    this->_inputs.push_back(&_in);
    this->_outputs.push_back(&_out);
  }

  Status getSteps(uint8_t& steps) const {
    return _steps.get(steps);
  }

  Status setSteps(uint8_t steps) {
    uint8_t pulses;
    auto status = _pulses.get(pulses);
    if (status != Status::Ok) {
      return status;
    }
    if (pulses > steps) {
      status = _pulses.set(steps);
      if (status != Status::Ok) {
        return status;
      }
    }
    return _steps.set(steps);
  }

  Status getPulses(uint8_t& pulses) const {
    return _pulses.get(pulses);
  }

  Status setPulses(uint8_t pulses) {
    uint8_t steps;
    auto status = _steps.get(steps);
    if (status != Status::Ok) {
      return status;
    }
    if (pulses > steps) {
      return Status::InvalidArgument;
    }
    return _pulses.set(pulses);
  }

  Status process(const TimeType&, const TimeType&) override {
    uint8_t numSteps, numPulses;
    auto status = _steps.get(numSteps);
    if (status != Status::Ok) {
      return status;
    }
    status = _pulses.get(numPulses);
    if (status != Status::Ok) {
      return status;
    }

    MessageType msg;
    while (_in.popMessage(msg) == Status::Ok) {
      if (stepIsOn(_currentStep, numSteps, numPulses)) {
        status = _out.pushToConnections(msg);
        if (status != Status::Ok) {
          return status;
        }
      }
      _currentStep = (_currentStep + 1) % numSteps;
    }

    return Status::Ok;
  }

private:
  static bool stepIsOn(uint8_t step, uint8_t numSteps, uint8_t numPulses) {
    return (step * numPulses) % numSteps < numPulses;
  }

  Param<uint8_t> _steps;
  Param<uint8_t> _pulses;
  InputType _in;
  OutputType _out;
  uint8_t _currentStep{0};
};
}
