#pragma once

#include <cassert>
#include "Message.h"
#include "Node.h"

namespace dc {
template<class DataType, class TimeType>
class PassthroughNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;
  using InputPortType = InputPort<MessageType>;
  using OutputPortType = OutputPort<MessageType>;

  PassthroughNode(size_t queueSize, size_t maxOutputConnections) {
    _input = NodeBase::addInputPort<MessageType>("in", queueSize);
    assert(_input != nullptr);
    _output = NodeBase::addOutputPort<MessageType>("out", maxOutputConnections);
    assert(_output != nullptr);
  }

  Status process(const TimeType&, const TimeType&) override {
    if (_output->getNumConnections() == 0) {
      return Status::Ok;
    }

    MessageType msg;
    while (popMessage(msg) == Status::Ok) {
      const auto status = _output->pushToConnections(msg);
      if (status != Status::Ok) {
        return status;
      }
    }
    return Status::Ok;
  }

  Status pushMessage(const MessageType& msg) {
    return _input->pushMessage(msg);
  }

  Status popMessage(MessageType& msg) {
    return _input->popMessage(msg);
  }

private:
  InputPortType* _input;
  OutputPortType* _output;
};
}
