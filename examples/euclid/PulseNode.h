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

  explicit PulseNode(const Param<TimeType>& rateParam,
                     size_t maxOutputConnections = 16) :
      _rate(rateParam),
      _out(this, "out", maxOutputConnections) {
    this->_outputs.push_back(&_out);
  }

  [[nodiscard]] bool getEnabled() const {
    return _enabled.get();
  }

  void setEnabled(bool enabled) {
    _enabled.set(enabled);
  }

  [[nodiscard]] TimeType getRate() const {
    return _rate.get();
  }

  [[nodiscard]] double getRateNormalized() const {
    return _rate.getNormalized();
  }

  void setRate(const TimeType& rate) {
    _rate.set(rate);
  }

  void setRateNormalized(double normalized) {
    _rate.setNormalized(normalized);
  }

  Status process(const TimeType& now, const TimeType& deltaTime) override {
    if (!_enabled.get()) {
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
    msg.data = _outputData;
    auto status = _out.pushToConnections(msg);
    if (status != Status::Ok) {
      return status;
    }
    TimeType rate = _rate.get();
    _nextPulse += rate;
    return Status::Ok;
  }

  BoolParam _enabled{false};
  Param<TimeType> _rate;
  DataType _outputData{};
  TimeType _nextPulse{0};
  OutputType _out;
};
}
