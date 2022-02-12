#pragma once

#include "dagnabbit/Message.h"
#include "dagnabbit/Node.h"
#include "dagnabbit/Param.h"

namespace dc::euclid {
template<class TimeType, class DataType>
class PulseNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;
  using OutputType = OutputPort<MessageType>;

  explicit PulseNode(const TimeType& rateMin,
                     const TimeType& rateMax,
                     const TimeType& rateDefault,
                     const TimeType& rateStep,
                     const DataType& pulseData,
                     size_t maxOutputConnections = 16) :
                     _rate(rateMin, rateMax, rateDefault, rateStep),
                     _pulseData(pulseData),
                     _out(this, "out", maxOutputConnections) {
    this->_outputs.push_back(&_out);
  }

  void setEnabled(bool enabled) {
    _enabled = enabled;
  }

  Status setRate(TimeType rate) {
    return _rate.set(rate);
  }

  Status process(const TimeType& now, const TimeType& deltaTime) override {
    if (!_enabled) {
      return Status::Ok;
    }

    const auto endTime = now + deltaTime;
    while (_nextPulse < endTime) {
      const auto status = doPulse();
      if (status != Status::Ok) {
        return status;
      }
    }

    return Status::Ok;
  }

private:
  Status doPulse() {
    MessageType msg;
    msg.time = _nextPulse;
    msg.data = _pulseData;
    auto status = _out.pushToConnections(msg);
    if (status != Status::Ok) {
      return status;
    }
    TimeType rate;
    status = _rate.get(rate);
    if (status != Status::Ok) {
      return status;
    }
    _nextPulse += rate;
    return Status::Ok;
  }

  bool _enabled{false};
  Param<TimeType> _rate;
  const DataType _pulseData;
  TimeType _nextPulse{0};
  OutputType _out;
};
}
