#include <gtest/gtest.h>
#include "../../third_party/rigtorp/MPMCQueue.h"
#include "../Message.h"
#include "../Node.h"

using namespace dc;

class PassthroughNode : public Node<float> {
public:
  using MessageType = Message<float, float>;
  using QueueType = rigtorp::MPMCQueue<MessageType>;

  PassthroughNode() : _inputQueue(16) {
    // input
    {
      Port::Config cfg;
      cfg.typeId = 1;
      cfg.maxConnections = 1;
      cfg.createMessageQueueFn = [this]() {
        return &_inputQueue;
      };
      this->_inputs.emplace_back(std::make_unique<Port>(cfg));
    }
    // output
    {
      Port::Config cfg;
      cfg.typeId = 1;
      cfg.maxConnections = 4;
      this->_outputs.emplace_back(std::make_unique<Port>(cfg));
    }
  }

  Status process(const float&, const float&) override {
    MessageType msg;
    while (_inputQueue.try_pop(msg)) {
      const auto status = _outputs[0]->frobConnections([&msg](Port* other) {
        void* qP;
        auto status = other->getMessageQueue(qP);
        if (status != Status::Ok) {
          return status;
        }
        auto q = static_cast<QueueType*>(qP);
        return q->try_push(msg) ? Status::Ok : Status::Full;
      });
      if (status != Status::Ok) {
        return status;
      }
    }
    return Status::Ok;
  }

  Status pushMessage(const MessageType& msg) {
    return _inputQueue.try_push(msg) ? Status::Ok : Status::Full;
  }

  Status popMessage(MessageType& msg) {
    return _inputQueue.try_pop(msg) ? Status::Ok : Status::Empty;
  }

private:
  QueueType _inputQueue;
};

TEST(Node, PassthroughNode) {
  PassthroughNode node;
  ASSERT_EQ(node.getNumInputs(), 1);
  ASSERT_EQ(node.getNumOutputs(), 1);

  PassthroughNode::MessageType msgIn;
  msgIn.data = 123.43f;
  msgIn.time = 8787.9f;
  ASSERT_EQ(node.pushMessage(msgIn), Status::Ok);
  PassthroughNode::MessageType msgOut;
  ASSERT_EQ(node.popMessage(msgOut), Status::Ok);
  ASSERT_FLOAT_EQ(msgOut.time, msgIn.time);
  ASSERT_FLOAT_EQ(msgOut.data, msgOut.data);
  ASSERT_EQ(node.popMessage(msgOut), Status::Empty);

  PassthroughNode node2;
  ASSERT_EQ(node2.connectInput(node, 0, 0), Status::Ok);
  msgIn.data = 52452.23432f;
  msgIn.time = 1452234.12f;
  ASSERT_EQ(node.pushMessage(msgIn), Status::Ok);
  ASSERT_EQ(node.process(0, 0), Status::Ok);
  ASSERT_EQ(node2.popMessage(msgOut), Status::Ok);
  ASSERT_FLOAT_EQ(msgOut.time, msgIn.time);
  ASSERT_FLOAT_EQ(msgOut.data, msgOut.data);
}
