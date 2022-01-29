#include <chrono>
#include <gtest/gtest.h>
#include "../Graph.h"
#include "../Message.h"

using namespace dc;

template<class DataType, class TimeType>
class PassthroughNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;
  using InputPortType = InputPort<MessageType>;
  using OutputPortType = OutputPort<MessageType>;

  PassthroughNode(size_t queueSize, size_t maxOutputConnections) :
      _input("in", queueSize),
      _output("out", maxOutputConnections) {
    // input
    this->_inputs.push_back(&_input);
    // output
    this->_outputs.push_back(&_output);
  }

  Status process(const TimeType&, const TimeType&) override {
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
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
