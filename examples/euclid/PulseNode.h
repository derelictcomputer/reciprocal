#pragma once

#include "dagnabbit/Message.h"
#include "dagnabbit/Node.h"
#include "dagnabbit/Param.h"

namespace dc::euclid {
template<class TimeType, class DataType>
class PulseNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;

  explicit PulseNode(const Param <TimeType>& rateParam, size_t maxOutputConnections = 16) :
      _rate(rateParam) {
    NodeBase::addOutputPort<MessageType>("out", maxOutputConnections);
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

    const auto rate = _rate.get();
    auto nextPulseTime = rate * std::floor(now / rate);
    if (nextPulseTime < now) {
      nextPulseTime += rate;
    }
    const auto endTime = now + deltaTime;
    MessageType msg;
    msg.data = _outputData;
    while (nextPulseTime < endTime) {
      msg.time = nextPulseTime;
      const auto status = NodeBase::pushOutputMessage(0, msg);
      if (status != Status::Ok) {
        return status;
      }
      nextPulseTime += rate;
    }

    return Status::Ok;
  }

private:
  BoolParam _enabled{"enabled", false};
  Param<TimeType> _rate;
  DataType _outputData{};
};
}
