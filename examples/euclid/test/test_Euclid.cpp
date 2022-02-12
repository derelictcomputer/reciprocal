#include <gtest/gtest.h>
#include "dagnabbit/PassthroughNode.h"
#include "../Euclid.h"

using namespace dc;
using namespace dc::euclid;

TEST(Euclid, Output) {
  using TimeType = double;
  const TimeType rateMin = 1.0 / 16.0;
  const TimeType rateMax = 4.0;
  const TimeType rateDef = 1.0;
  const TimeType rateStep = 0;
  const uint8_t pulseDef = 4;
  const uint8_t stepDef = 16;
  Euclid<TimeType> euclid(rateMin, rateMax, rateDef, rateStep, stepDef, pulseDef);
  ASSERT_EQ(euclid.setEnabled(true), Status::Ok);

  TimeType now{0};
  for (size_t i = 0; i < stepDef * 2; ++i) {
    ASSERT_EQ(euclid.process(rateDef), Status::Ok);
    Message<Euclid<TimeType>::DataType, TimeType> msg;
    auto status = euclid.popOutputMessage(msg);
    if (i % 4 != 0) {
      ASSERT_EQ(status, Status::Empty);
    }
    else {
      ASSERT_EQ(status, Status::Ok);
      ASSERT_DOUBLE_EQ(now, msg.time);
      ASSERT_TRUE(msg.data);
    }
    now += rateDef;
  }
}

TEST(EuclidNode, Throughput) {
  using TimeType = double;
  using DataType = bool;

  Graph<TimeType> graph(16, 3);

  PassthroughNode<DataType, TimeType>* inputNode{nullptr};
  NodeId inputNodeId{InvalidNodeId};
  {
    const auto status = graph.addNode(
        [&inputNode]() {
          inputNode = new PassthroughNode<DataType, TimeType>(16, 1);
          return inputNode;
        },
        [&inputNodeId](Status status, NodeId id) {
          ASSERT_EQ(status, Status::Ok);
          ASSERT_NE(id, dc::InvalidNodeId);
          inputNodeId = id;
        });
    ASSERT_EQ(status, Status::Ok);
  }

  EuclidNode<TimeType, DataType>* euclidNode{nullptr};
  NodeId euclidNodeId{InvalidNodeId};
  {
    const auto status = graph.addNode(
        [&euclidNode]() {
          euclidNode = new EuclidNode<TimeType, DataType>(8, 16, 16, 1);
          return euclidNode;
        },
        [&euclidNodeId](Status status, NodeId id) {
          ASSERT_EQ(status, Status::Ok);
          ASSERT_NE(id, dc::InvalidNodeId);
          euclidNodeId = id;
        });
    ASSERT_EQ(status, Status::Ok);
  }

  PassthroughNode<DataType, TimeType>* outputNode{nullptr};
  NodeId outputNodeId{InvalidNodeId};
  {
    const auto status = graph.addNode(
        [&outputNode]() {
          outputNode = new PassthroughNode<DataType, TimeType>(16, 0);
          return outputNode;
        },
        [&outputNodeId](Status status, NodeId id) {
          ASSERT_EQ(status, Status::Ok);
          ASSERT_NE(id, dc::InvalidNodeId);
          outputNodeId = id;
        });
    ASSERT_EQ(status, Status::Ok);
  }

  // process so we get our node ids
  {
    const auto status = graph.process();
    ASSERT_EQ(status, Status::Ok);
  }

  // connect the chain
  {
    const auto status = graph.connectNodes(inputNodeId, 0, euclidNodeId, 0,
                                           [](Status status, NodeId, size_t, NodeId, size_t) {
                                             ASSERT_EQ(status, Status::Ok);
                                           });
    ASSERT_EQ(status, Status::Ok);
  }
  {
    const auto status = graph.connectNodes(euclidNodeId, 0, outputNodeId, 0,
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

  // push some pulses to the euclid node, expect to get the filtered output
  const uint8_t numPulses = 4;
  const uint8_t numSteps = 8;
  ASSERT_EQ(euclidNode->setPulses(numPulses), Status::Ok);
  ASSERT_EQ(euclidNode->setSteps(numSteps), Status::Ok);
  TimeType now{0};
  const TimeType interval{2};
  for (size_t i = 0; i < numSteps * 2; ++i) {
    Message<DataType, TimeType> msg;
    msg.time = now;
    msg.data = true;
    ASSERT_EQ(inputNode->pushMessage(msg), Status::Ok);
    ASSERT_EQ(graph.process(interval), Status::Ok);
    if (i % 2 == 0) {
      Message<DataType, TimeType> msgOut;
      ASSERT_EQ(outputNode->popMessage(msgOut), Status::Ok);
      ASSERT_EQ(msgOut.time, msg.time);
      ASSERT_EQ(msgOut.data, msg.data);
    }
    now += interval;
  }
}

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
