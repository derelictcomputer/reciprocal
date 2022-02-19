#pragma once

#include <cassert>
#include "Message.h"
#include "Node.h"

namespace dc {
template<class DataType, class TimeType>
class PassthroughNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;

  PassthroughNode(size_t queueSize, size_t maxOutputConnections) : _outputQ(queueSize) {
    NodeBase::addInputPort<MessageType>("in", queueSize);
    NodeBase::addOutputPort<MessageType>("out", maxOutputConnections);
  }

  Status process(const TimeType&, const TimeType&) override {
    MessageType msg;
    while (NodeBase::popInputMessage(0, msg) == Status::Ok) {
      auto status = NodeBase::pushOutputMessage(0, msg);
      if (status == Status::NoConnection) {
        status = _outputQ.push(msg);
        if (status != Status::Ok) {
          return status;
        }
      }
      else if (status != Status::Ok) {
        return status;
      }
    }
    return Status::Ok;
  }

  Status pushMessage(const MessageType& msg) {
    return NodeBase::pushInputMessage(0, msg);
  }

  Status popMessage(MessageType& msg) {
    return _outputQ.pop(msg);
  }

private:
  SPSCQ<MessageType> _outputQ;
};
}
