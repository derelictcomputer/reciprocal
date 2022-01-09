#include <gtest/gtest.h>
#include "../../third_party/rigtorp/MPMCQueue.h"
#include "../Message.h"
#include "../Node.h"

using namespace dc;

class PassthroughNode : public Node<float> {
public:
  using MessageType = Message<float, float>;
  using InputPortType = InputPort<MessageType>;
  using OutputPortType = OutputPort<MessageType>;

  PassthroughNode() {
    // input
    {
      IPort::Config cfg;
      cfg.typeId = 1;
      cfg.maxConnections = 1;
      this->_inputs.emplace_back(std::make_unique<InputPortType>(cfg, 16));
    }
    // output
    {
      IPort::Config cfg;
      cfg.typeId = 1;
      cfg.maxConnections = 4;
      this->_outputs.emplace_back(std::make_unique<OutputPortType>(cfg));
    }
  }

  Status process(const float&, const float&) override {
    MessageType msg;
    while (popMessage(msg) == Status::Ok) {
      auto output = dynamic_cast<OutputPortType*>(_outputs[0].get());
      const auto status = output->pushToConnections(msg);
      if (status != Status::Ok) {
        return status;
      }
    }
    return Status::Ok;
  }

  Status pushMessage(const MessageType& msg) {
    auto input = dynamic_cast<InputPortType*>(_inputs[0].get());
    if (input != nullptr) {
      return input->pushMessage(msg);
    }
    return Status::Fail;
  }

  Status popMessage(MessageType& msg) {
    auto input = dynamic_cast<InputPortType*>(_inputs[0].get());
    if (input != nullptr) {
      return input->popMessage(msg);
    }
    return Status::Fail;
  }
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
