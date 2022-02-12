#include <gtest/gtest.h>
#include "dagnabbit/Graph.h"
#include "dagnabbit/dev_helpers/PassthroughNode.h"
#include "../PulseNode.h"

using namespace dc;
using namespace dc::euclid;

TEST(PulseNode, Output) {
  using TimeType = double;
  using DataType = bool;
  const TimeType min = 1.0 / 16.0;
  const TimeType max = 4.0;
  const TimeType def = 1.0;
  const TimeType step = 0;
  const TimeType rate = 0.5;
  const size_t maxOutputConnections = 32;

  Graph<TimeType> graph(maxOutputConnections * 2, maxOutputConnections * 2);

  // add a pulse node to the graph
  PulseNode<TimeType, DataType>* pulseNode{nullptr};
  NodeId pulseNodeId{InvalidNodeId};
  {
    const auto status = graph.addNode(
        [min, max, def, step, &pulseNode]() {
          pulseNode = new PulseNode<TimeType, DataType>(min, max, def, step, true, maxOutputConnections);
          return pulseNode;
        },
        [&pulseNodeId](Status status, NodeId nodeId) {
          ASSERT_EQ(status, Status::Ok);
          ASSERT_NE(nodeId, dc::InvalidNodeId);
          pulseNodeId = nodeId;
        });
    ASSERT_EQ(status, Status::Ok);
  }

  // create passthrough nodes to receive the pulse
  struct PassthroughNodeInfo {
    PassthroughNode<DataType, TimeType>* node{nullptr};
    NodeId id{InvalidNodeId};
  };
  std::vector<PassthroughNodeInfo> passthroughNodes(maxOutputConnections);
  for (auto& info: passthroughNodes) {
    const auto status = graph.addNode(
        [&info]() {
          info.node = new PassthroughNode<DataType, TimeType>(16, 0);
          return info.node;
        },
        [&info](Status status, NodeId nodeId) {
          ASSERT_EQ(status, Status::Ok);
          ASSERT_NE(nodeId, dc::InvalidNodeId);
          info.id = nodeId;
        });
    ASSERT_EQ(status, Status::Ok);
  }
  ASSERT_EQ(passthroughNodes.size(), maxOutputConnections);

  // process so we get our node ids
  {
    const auto status = graph.process();
    ASSERT_EQ(status, Status::Ok);
  }

  // connect the passthrough nodes to the pulse node
  for (const auto& info: passthroughNodes) {
    const auto status = graph.connectNodes(pulseNodeId, 0, info.id, 0,
                                           [](Status status, NodeId, size_t, NodeId, size_t) {
                                             ASSERT_EQ(status, Status::Ok);
                                           });
    ASSERT_EQ(status, Status::Ok);
  }

  // process so the connections go through
  {
    const auto status = graph.process();
    ASSERT_EQ(status, Status::Ok);
  }

  // start the pulse and process, expect all the passthrough nodes to get a pulse
  auto now = TimeType(0);
  pulseNode->setEnabled(true);
  ASSERT_EQ(pulseNode->setRate(rate), Status::Ok);
  for (size_t i = 0; i < 16; ++i) {
    ASSERT_EQ(graph.process(rate), Status::Ok);
    for (auto& info: passthroughNodes) {
      Message<DataType, TimeType> msg;
      ASSERT_EQ(info.node->popMessage(msg), Status::Ok);
      ASSERT_TRUE(msg.data);
      ASSERT_DOUBLE_EQ(msg.time, now);
    }
    now += rate;
  }
}
