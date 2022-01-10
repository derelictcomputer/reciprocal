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

  PassthroughNode() : _input("in", 16), _output("out", 4) {
    // input
    this->_inputs.push_back(&_input);
    // output
    this->_outputs.push_back(&_output);
  }

  Status process(const float&, const float&) override {
    MessageType msg;
    while (popMessage(msg) == Status::Ok) {
      const auto status = _output.pushToConnections(msg);
      if (status != Status::Ok) {
        return status;
      }
    }
    return Status::Ok;
  }

  Status pushMessage(const MessageType& msg) {
    return _input.pushMessage(msg);
  }

  Status popMessage(MessageType& msg) {
    return _input.popMessage(msg);
  }

private:
  InputPortType _input;
  OutputPortType _output;
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
