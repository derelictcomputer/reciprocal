#include <gtest/gtest.h>
#include "third_party/rigtorp/MPMCQueue.h"
#include "dagnabbit/PassthroughNode.h"

using namespace dc;

TEST(Node, PassthroughNode) {
  using NodeType = PassthroughNode<float, float>;
  NodeType node(16, 4);
  ASSERT_EQ(node.getNumInputs(), 1);
  ASSERT_EQ(node.getNumOutputs(), 1);

  NodeType::MessageType msgIn;
  msgIn.data = 123.43f;
  msgIn.time = 8787.9f;
  ASSERT_EQ(node.pushMessage(msgIn), Status::Ok);
  NodeType::MessageType msgOut;
  ASSERT_EQ(node.popMessage(msgOut), Status::Ok);
  ASSERT_FLOAT_EQ(msgOut.time, msgIn.time);
  ASSERT_FLOAT_EQ(msgOut.data, msgOut.data);
  ASSERT_EQ(node.popMessage(msgOut), Status::Empty);

  NodeType node2(16, 4);
  ASSERT_EQ(node2.connectInput(node, 0, 0), Status::Ok);
  msgIn.data = 52452.23432f;
  msgIn.time = 1452234.12f;
  ASSERT_EQ(node.pushMessage(msgIn), Status::Ok);
  ASSERT_EQ(node.process(0, 0), Status::Ok);
  ASSERT_EQ(node2.popMessage(msgOut), Status::Ok);
  ASSERT_FLOAT_EQ(msgOut.time, msgIn.time);
  ASSERT_FLOAT_EQ(msgOut.data, msgOut.data);
}

TEST(Node, ConnectDisconnect) {
  using NodeType = PassthroughNode<double, size_t>;
  NodeType node1(32, 2);
  NodeType node2(32, 2);

  // valid connect
  ASSERT_EQ(node2.connectInput(node1, 0, 0), Status::Ok);

  // valid disconnect
  ASSERT_EQ(node2.disconnectInput(node1, 0, 0), Status::Ok);

  // disconnect when there wasn't a connection
  ASSERT_EQ(node2.disconnectInput(node1, 0, 0), Status::NotFound);

  // connect to a port that's not there
  ASSERT_EQ(node1.connectInput(node2, 0, 1), Status::OutOfRange);

  // connect to self
  ASSERT_EQ(node1.connectInput(node1, 0, 0), Status::InvalidArgument);
}
