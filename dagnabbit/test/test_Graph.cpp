#include <chrono>
#include <gtest/gtest.h>
#include "../Graph.h"
#include "../dev_helpers/PassthroughNode.h"

using namespace dc;

TEST(Graph, AddRemove) {
  using TimeType = double;
  const size_t asyncQueueSize = 32;
  const size_t maxNodes = 1024;

  Graph<TimeType> graph(asyncQueueSize, maxNodes);

  ASSERT_EQ(graph.capacity, maxNodes);
  ASSERT_EQ(graph.size(), 0);

  // add a valid node and expect that to work
  std::atomic<NodeId> validNodeId = InvalidNodeId;
  {
    std::atomic<bool> gotCb{false};
    ASSERT_EQ(graph.addNode(
        []() {
          return new PassthroughNode<int, TimeType>(1, 1);
        },
        [&gotCb, &validNodeId](Status status, NodeId nodeId) {
          gotCb = true;
          ASSERT_EQ(status, Status::Ok);
          ASSERT_NE(nodeId, InvalidNodeId);
          validNodeId = nodeId;
        }), Status::Ok);

    ASSERT_FALSE(gotCb);
    ASSERT_EQ(graph.size(), 0);

    ASSERT_EQ(graph.process(), Status::Ok);

    ASSERT_TRUE(gotCb);
    ASSERT_EQ(graph.size(), 1);
  }

  // remove that node and expect it to succeed
  {
    std::atomic<bool> gotCb{false};
    ASSERT_EQ(graph.removeNode(validNodeId, [&validNodeId, &gotCb](Status status, NodeId nodeId) {
      gotCb = true;
      ASSERT_EQ(status, Status::Ok);
      ASSERT_EQ(nodeId, validNodeId.load());
    }), Status::Ok);

    ASSERT_FALSE(gotCb);
    ASSERT_EQ(graph.size(), 1);

    ASSERT_EQ(graph.process(), Status::Ok);

    ASSERT_TRUE(gotCb);
    ASSERT_EQ(graph.size(), 0);
  }

  // try to add an invalid node, expect that to fail
  {
    ASSERT_EQ(graph.addNode([]() { return nullptr; }, [](Status, NodeId) {}), Status::InvalidArgument);
    ASSERT_EQ(graph.size(), 0);
    ASSERT_EQ(graph.process(), Status::Ok);
    ASSERT_EQ(graph.size(), 0);
  }

  // try to remove nodes that are not there
  {
    // Special fast path for the invalid node id.
    ASSERT_EQ(graph.removeNode(InvalidNodeId, [](Status, NodeId) {}), Status::InvalidArgument);

    // Regular path for a node id that's valid, but not in the graph.
    std::atomic<bool> gotCb{false};
    const NodeId id = 1;
    ASSERT_EQ(graph.removeNode(id, [id, &gotCb](Status status, NodeId nodeId) {
      gotCb = true;
      ASSERT_EQ(status, Status::NotFound);
      ASSERT_EQ(nodeId, id);
    }), Status::Ok);

    ASSERT_FALSE(gotCb);
    ASSERT_EQ(graph.size(), 0);

    ASSERT_EQ(graph.process(), Status::Ok);

    ASSERT_TRUE(gotCb);
    ASSERT_EQ(graph.size(), 0);
  }
}

TEST(Graph, AddRemoveMT) {
  using TimeType = int32_t;
  const size_t asyncQueueSize = 512;
  const size_t maxNodes = 64;

  Graph<TimeType> graph(asyncQueueSize, maxNodes);

  std::atomic<bool> runProcessThread{true};
  std::thread processThread([&runProcessThread, &graph]() {
    while (runProcessThread) {
      graph.process();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  // run a few threads to add nodes and wait for them to get added
  const size_t numAddRemoveThreads = 16;
  std::vector<std::thread> addRemoveThreads;
  for (size_t i = 0; i < numAddRemoveThreads; ++i) {
    addRemoveThreads.emplace_back([&graph]() {
      std::atomic<NodeId> nodeId{InvalidNodeId};

      // add the node
      ASSERT_EQ(graph.addNode(
          []() {
            return new PassthroughNode<double, TimeType>(1, 1);
          },
          [&nodeId](Status status, NodeId id) {
            ASSERT_EQ(status, Status::Ok);
            ASSERT_NE(id, InvalidNodeId);
            nodeId = id;
          }), Status::Ok);

      // wait for the node to be added
      while (nodeId == InvalidNodeId) {
        std::this_thread::yield();
      }

      // remove the node
      ASSERT_EQ(graph.removeNode(nodeId, [&nodeId](Status status, NodeId id) {
        ASSERT_EQ(status, Status::Ok);
        ASSERT_EQ(id, nodeId.load());
        nodeId = InvalidNodeId;
      }), Status::Ok);

      // wait for the node to be removed
      while (nodeId != InvalidNodeId) {
        std::this_thread::yield();
      }
    });
  }

  for (auto& thread: addRemoveThreads) {
    thread.join();
  }

  while (graph.size() > 0) {
    std::this_thread::yield();
  }
  
  runProcessThread = false;
  processThread.join();

  ASSERT_EQ(graph.size(), 0);
}

TEST(Graph, FillEmpty) {
  using TimeType = uint16_t;
  const size_t asyncQueueSize = 64;
  const size_t maxNodes = 64;

  Graph<TimeType> graph(asyncQueueSize, maxNodes);

  for (size_t round = 0; round < 4; ++round) {
    // fill the graph
    std::vector<NodeId> nodeIds;
    nodeIds.reserve(maxNodes);
    const auto addCb = [&nodeIds](Status status, NodeId nodeId) {
      ASSERT_EQ(status, Status::Ok);
      ASSERT_NE(nodeId, InvalidNodeId);
      nodeIds.push_back(nodeId);
    };
    for (size_t i = 0; i < maxNodes; ++i) {
      ASSERT_EQ(graph.addNode(
          []() { return new PassthroughNode<int, TimeType>(1, 1); },
          addCb), Status::Ok);
    }

    // process
    ASSERT_EQ(graph.process(), Status::Ok);
    ASSERT_EQ(graph.size(), maxNodes);

    // empty the graph
    const auto removeCb = [](Status status, NodeId nodeId) {
      ASSERT_EQ(status, Status::Ok);
      ASSERT_NE(nodeId, InvalidNodeId);
    };
    for (auto id: nodeIds) {
      ASSERT_EQ(graph.removeNode(id, removeCb), Status::Ok);
    }

    // process
    ASSERT_EQ(graph.process(), Status::Ok);
    ASSERT_EQ(graph.size(), 0);
  }
}

TEST(Graph, ConnectDisconnect) {
  using TimeType = int8_t;
  const size_t asyncQueueSize = 16;
  const size_t maxNodes = 8;

  Graph<TimeType> graph(asyncQueueSize, maxNodes);

  // add two nodes
  const auto createFn = []() {
    return new PassthroughNode<float, TimeType>(1, 1);
  };
  NodeId nodeId1{InvalidNodeId};
  ASSERT_EQ(graph.addNode(createFn, [&nodeId1](Status status, NodeId nodeId) {
    ASSERT_EQ(status, Status::Ok);
    ASSERT_NE(nodeId, InvalidNodeId);
    nodeId1 = nodeId;
  }), Status::Ok);
  NodeId nodeId2{InvalidNodeId};
  ASSERT_EQ(graph.addNode(createFn, [&nodeId2](Status status, NodeId nodeId) {
    ASSERT_EQ(status, Status::Ok);
    ASSERT_NE(nodeId, InvalidNodeId);
    nodeId2 = nodeId;
  }), Status::Ok);

  // process to actually add them
  ASSERT_EQ(graph.process(), Status::Ok);
  ASSERT_NE(nodeId1, InvalidNodeId);
  ASSERT_NE(nodeId2, InvalidNodeId);

  // connect them
  ASSERT_EQ(
      graph.connectNodes(nodeId1, 0, nodeId2, 0,
                         [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                           ASSERT_EQ(status, Status::Ok);
                           ASSERT_EQ(from, nodeId1);
                           ASSERT_EQ(fromIdx, 0);
                           ASSERT_EQ(to, nodeId2);
                           ASSERT_EQ(toIdx, 0);
                         }),
      Status::Ok);

  // process to actually connect them
  ASSERT_EQ(graph.process(), Status::Ok);

  // disconnect them
  ASSERT_EQ(
      graph.disconnectNodes(nodeId1, 0, nodeId2, 0,
                            [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                              ASSERT_EQ(status, Status::Ok);
                              ASSERT_EQ(from, nodeId1);
                              ASSERT_EQ(fromIdx, 0);
                              ASSERT_EQ(to, nodeId2);
                              ASSERT_EQ(toIdx, 0);
                            }),
      Status::Ok);

  // process to actually disconnect them
  ASSERT_EQ(graph.process(), Status::Ok);

  // try to do some invalid connections
  ASSERT_EQ(
      graph.connectNodes(nodeId1, 1, nodeId2, 0,
                         [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                           ASSERT_EQ(status, Status::OutOfRange);
                           ASSERT_EQ(from, nodeId1);
                           ASSERT_EQ(fromIdx, 1);
                           ASSERT_EQ(to, nodeId2);
                           ASSERT_EQ(toIdx, 0);
                         }),
      Status::Ok);
  ASSERT_EQ(
      graph.connectNodes(nodeId1, 0, nodeId2, 1,
                         [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                           ASSERT_EQ(status, Status::OutOfRange);
                           ASSERT_EQ(from, nodeId1);
                           ASSERT_EQ(fromIdx, 0);
                           ASSERT_EQ(to, nodeId2);
                           ASSERT_EQ(toIdx, 1);
                         }),
      Status::Ok);
  ASSERT_EQ(
      graph.connectNodes(nodeId1, 0, maxNodes + 1, 0,
                         [nodeId1](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                           ASSERT_EQ(status, Status::NotFound);
                           ASSERT_EQ(from, nodeId1);
                           ASSERT_EQ(fromIdx, 0);
                           ASSERT_EQ(to, maxNodes + 1);
                           ASSERT_EQ(toIdx, 0);
                         }),
      Status::Ok);
  ASSERT_EQ(
      graph.connectNodes(InvalidNodeId, 0, nodeId2, 0,
                         [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                           ASSERT_EQ(status, Status::Ok);
                           ASSERT_EQ(from, nodeId1);
                           ASSERT_EQ(fromIdx, 0);
                           ASSERT_EQ(to, nodeId2);
                           ASSERT_EQ(toIdx, 0);
                         }),
      Status::InvalidArgument);

  // try to do some invalid disconnections
  ASSERT_EQ(
      graph.disconnectNodes(nodeId1, 0, nodeId2, 0,
                            [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                              ASSERT_EQ(status, Status::NotFound);
                              ASSERT_EQ(from, nodeId1);
                              ASSERT_EQ(fromIdx, 0);
                              ASSERT_EQ(to, nodeId2);
                              ASSERT_EQ(toIdx, 0);
                            }),
      Status::Ok);
  ASSERT_EQ(
      graph.connectNodes(InvalidNodeId, 0, nodeId2, 0,
                         [nodeId1, nodeId2](Status status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx) {
                           ASSERT_EQ(status, Status::Ok);
                           ASSERT_EQ(from, nodeId1);
                           ASSERT_EQ(fromIdx, 0);
                           ASSERT_EQ(to, nodeId2);
                           ASSERT_EQ(toIdx, 0);
                         }),
      Status::InvalidArgument);

  // process so the async calls go through
  ASSERT_EQ(graph.process(), Status::Ok);
}

TEST(Graph, ProcessSimpleChain) {
  using TimeType = float;
  const size_t numNodes = 4;
  Graph<TimeType> graph(numNodes * 4, numNodes);

  using DataType = char;
  using NodeType = PassthroughNode<DataType , TimeType>;
  NodeType* firstNode{nullptr};
  NodeType* lastNode{nullptr};
  std::vector<NodeId> nodeIds;

  // make the nodes
  for (size_t i = 0; i < numNodes; ++i) {
    ASSERT_EQ(graph.addNode(
        [&firstNode, &lastNode]() {
          auto node = new NodeType(1, 1);
          if (firstNode == nullptr) {
            firstNode = node;
          }
          lastNode = node;
          return node;
        },
        [&nodeIds](Status status, NodeId nodeId) {
          ASSERT_EQ(status, Status::Ok);
          nodeIds.push_back(nodeId);
        }), Status::Ok);
  }

  ASSERT_EQ(graph.process(), Status::Ok);

  // connect the nodes
  for (size_t i = 1; i < numNodes; ++i) {
    ASSERT_EQ(graph.connectNodes(nodeIds[i - 1], 0, nodeIds[i], 0,
                                 [](Status status, NodeId, size_t, NodeId, size_t) {
                                   ASSERT_EQ(status, Status::Ok);
                                 }), Status::Ok);
  }

  // push some data to the first node and process
  using MessageType = Message<DataType, TimeType>;
  MessageType msg;
  msg.data = '!';
  msg.time = 123.45f;
  ASSERT_EQ(firstNode->pushMessage(msg), Status::Ok);
  ASSERT_EQ(graph.process(), Status::Ok);
  MessageType msgOut;
  ASSERT_EQ(lastNode->popMessage(msgOut), Status::Ok);
  ASSERT_EQ(msgOut.data, msg.data);
  ASSERT_FLOAT_EQ(msgOut.time, msg.time);
}
