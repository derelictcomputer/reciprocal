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
    std::cout << "Starting round " << round << std::endl;
    // fill the graph
    std::vector<NodeId> nodeIds;
    nodeIds.reserve(maxNodes);
    const auto addCb = [&nodeIds](Status status, NodeId nodeId) {
      ASSERT_EQ(status, Status::Ok);
      ASSERT_NE(nodeId, InvalidNodeId);
      nodeIds.push_back(nodeId);
    };
    std::cout << "Adding nodes\n";
    for (size_t i = 0; i < maxNodes; ++i) {
      ASSERT_EQ(graph.addNode(
          []() { return new PassthroughNode<int, TimeType>(1, 1); },
          addCb), Status::Ok);
    }

    // process
    std::cout << "Processing\n";
    ASSERT_EQ(graph.process(), Status::Ok);
    ASSERT_EQ(graph.size(), maxNodes);

    // empty the graph
    const auto removeCb = [](Status status, NodeId nodeId) {
      ASSERT_EQ(status, Status::Ok);
      ASSERT_NE(nodeId, InvalidNodeId);
    };
    std::cout << "Removing nodes\n";
    for (auto id: nodeIds) {
      ASSERT_EQ(graph.removeNode(id, removeCb), Status::Ok);
    }

    // process
    std::cout << "Processing\n";
    ASSERT_EQ(graph.process(), Status::Ok);
    ASSERT_EQ(graph.size(), 0);

    // let the garbage collector run
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
