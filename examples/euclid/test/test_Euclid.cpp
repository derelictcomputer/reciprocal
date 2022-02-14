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
  euclid.setParamNormalized(Euclid<TimeType>::ParamId::Enable, 1);

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
    }
    now += rateDef;
  }
}

TEST(Euclid, Params) {
  using TimeType = double;
  const TimeType rateMin = 1.0 / 16.0;
  const TimeType rateMax = 4.0;
  const TimeType rateDef = 1.0;
  const TimeType rateStep = 0;
  const uint8_t pulseDef = 4;
  const uint8_t stepDef = 16;
  Euclid<TimeType> euclid(rateMin, rateMax, rateDef, rateStep, stepDef, pulseDef);
  {
    ASSERT_EQ(euclid.setEnabled(true), Status::Ok);
    bool actualEnabled{false};
    ASSERT_EQ(euclid.getEnabled(actualEnabled), Status::Ok);
    ASSERT_TRUE(actualEnabled);
  }
  {
    TimeType actualRate{0};
    ASSERT_EQ(euclid.getRate(actualRate), Status::Ok);
    ASSERT_DOUBLE_EQ(actualRate, rateDef);
    ASSERT_EQ(euclid.setRate(rateMax), Status::Ok);
    ASSERT_EQ(euclid.getRate(actualRate), Status::Ok);
    ASSERT_DOUBLE_EQ(actualRate, rateMax);
  }
  {
    uint8_t actualPulses{0};
    ASSERT_EQ(euclid.getPulses(actualPulses), Status::Ok);
    ASSERT_EQ(actualPulses, pulseDef);
    const uint8_t newPulses = 8;
    ASSERT_EQ(euclid.setPulses(newPulses), Status::Ok);
    ASSERT_EQ(euclid.getPulses(actualPulses), Status::Ok);
    ASSERT_EQ(actualPulses, newPulses);
  }
  {
    uint8_t actualSteps{0};
    ASSERT_EQ(euclid.getSteps(actualSteps), Status::Ok);
    ASSERT_EQ(actualSteps, stepDef);
    const uint8_t newSteps = 15;
    ASSERT_EQ(euclid.setSteps(newSteps), Status::Ok);
    ASSERT_EQ(euclid.getSteps(actualSteps), Status::Ok);
    ASSERT_EQ(actualSteps, newSteps);
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
          Param<uint8_t> pulsesParam{1, 16, 8, 1};
          Param<uint8_t> stepsParam{1, 16, 16, 1};
          euclidNode = new EuclidNode<TimeType, DataType>(pulsesParam, stepsParam, 16, 1);
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
  euclidNode->setPulses(numPulses);
  euclidNode->setSteps(numSteps);
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
          Param<TimeType> rateParam{min, max, def, step};
          pulseNode = new PulseNode<TimeType, DataType>(rateParam, maxOutputConnections);
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
  pulseNode->setRate(rate);
  for (size_t i = 0; i < 16; ++i) {
    ASSERT_EQ(graph.process(now, rate), Status::Ok);
    for (auto& info: passthroughNodes) {
      Message<DataType, TimeType> msg;
      const auto status = info.node->popMessage(msg);
      ASSERT_EQ(status, Status::Ok);
      ASSERT_DOUBLE_EQ(msg.time, now);
    }
    now += rate;
  }
}
