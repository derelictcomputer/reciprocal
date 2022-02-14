#include <thread>
#include <benchmark/benchmark.h>
#include "../Graph.h"
#include "dagnabbit/PassthroughNode.h"

using namespace dc;

template<class TimeType>
static void Graph_AddRemove(benchmark::State& state) {
  const auto createFn = []() { return new PassthroughNode<float, TimeType>(1, 1); };
  Graph<TimeType> graph(8, 8);

  std::atomic<NodeId> nodeId{InvalidNodeId};

  // alternate adding and removing nodes
  for (auto _ : state) {
    // add node
    if (nodeId == InvalidNodeId)
    {
      std::atomic<size_t> cbCount{0};
      std::atomic<bool> error{false};
      const auto cb = [&cbCount, &error, &nodeId](Status status, NodeId id) {
        if (status != Status::Ok) {
          error = true;
        }
        ++cbCount;
        nodeId = id;
      };

      // add the node
      if (graph.addNode(createFn, cb) != Status::Ok) {
        state.SkipWithError("Failed to add node.");
        return;
      }

      // process, which will flush the async queue
      const auto status = graph.process();
      if (status != Status::Ok || error || cbCount != 1 || graph.size() != 1) {
        state.SkipWithError("Error during process after remove.");
        return;
      }
    }
    // remove node
    else {
      std::atomic<size_t> cbCount{0};
      std::atomic<bool> error{false};
      const auto cb = [&nodeId, &cbCount, &error](Status status, NodeId) {
        if (status != Status::Ok) {
          error = true;
        }
        ++cbCount;
        nodeId = InvalidNodeId;
      };

      // remove the node
      if (graph.removeNode(nodeId, cb) != Status::Ok) {
        state.SkipWithError("Failed to remove node.");
        return;
      }

      // process, which will flush the async queue
      const auto status = graph.process();
      if (status != Status::Ok || error || cbCount != 1 || graph.size() != 0) {
        state.SkipWithError("Error during process after remove.");
        return;
      }
    }
  }
}

BENCHMARK(Graph_AddRemove<double>);

template<class DataType, class TimeType>
static void Graph_ConnectDisconnect(benchmark::State& state) {
  const auto createFn = []() { return new PassthroughNode<DataType, TimeType>(1, 1); };
  Graph<TimeType> graph(8, 8);

  // create a source node
  std::atomic<bool> cbError{false};
  NodeId sourceNode{InvalidNodeId};
  auto status = graph.addNode(createFn, [&cbError, &sourceNode](Status status, NodeId nodeId) {
    if (status != Status::Ok) {
      cbError = true;
    }
    sourceNode = nodeId;
  });
  if (status != Status::Ok) {
    state.SkipWithError("Failed to create source node.");
    return;
  }

  // create a destination node
  NodeId destinationNode{InvalidNodeId};
  status = graph.addNode(createFn, [&cbError, &destinationNode](Status status, NodeId nodeId) {
    if (status != Status::Ok) {
      cbError = true;
    }
    destinationNode = nodeId;
  });
  if (status != Status::Ok) {
    state.SkipWithError("Failed to create source node.");
    return;
  }

  // process and make sure everything got created
  status = graph.process();

  if (status != Status::Ok || cbError || sourceNode == InvalidNodeId || graph.size() != 2) {
    state.SkipWithError("Error processing after adding nodes");
    return;
  }

  // alternate connecting and disconnecting the nodes
  bool connect{true};
  for (auto _: state) {
    // connect the nodes
    if (connect) {
      status = graph.connectNodes(sourceNode, 0, destinationNode, 0, [&cbError](
          Status status,
          NodeId,
          size_t,
          NodeId,
          size_t) {
        if (status != Status::Ok) {
          cbError = true;
        }
      });
      if (status != Status::Ok) {
        state.SkipWithError("Failed to connect.");
        return;
      }
    }
    else {
      status = graph.disconnectNodes(sourceNode, 0, destinationNode, 0, [&cbError](
          Status status,
          NodeId,
          size_t,
          NodeId,
          size_t) {
        if (status != Status::Ok) {
          cbError = true;
        }
      });
      if (status != Status::Ok) {
        state.SkipWithError("Failed to connect a node.");
        return;
      }
    }
    connect = !connect;

    // process
    status = graph.process();
    if (status != Status::Ok || cbError) {
      state.SkipWithError("Error processing after connecting or disconnecting nodes");
      return;
    }
  }
}

BENCHMARK(Graph_ConnectDisconnect<double, double>);

template<class DataType, class TimeType, size_t NumNodes>
static void Graph_Process_PassthroughChain(benchmark::State& state) {
  Graph<TimeType> graph(NumNodes * 4, NumNodes);
  using NodeType = PassthroughNode<DataType, TimeType>;
  NodeType* firstNode{nullptr};
  NodeType* lastNode{nullptr};

  // make the nodes
  std::vector<NodeId> nodeIds;
  {
    bool cbError{false};
    for (size_t i = 0; i < NumNodes; ++i) {
      const auto status = graph.addNode(
          [&firstNode, &lastNode]() {
            auto node = new NodeType(1, 1);
            if (firstNode == nullptr) {
              firstNode = node;
            }
            lastNode = node;
            return node;
          },
          [&cbError, &nodeIds](Status status, NodeId nodeId) {
            if (status != Status::Ok) {
              cbError = true;
            }
            nodeIds.push_back(nodeId);
          });
      if (status != Status::Ok) {
        state.SkipWithError("Failed to create node");
        return;
      }
    }

    // process and make sure everything got created
    {
      const auto status = graph.process();

      if (status != Status::Ok || cbError || graph.size() < NumNodes || firstNode == nullptr || lastNode == nullptr) {
        state.SkipWithError("Error processing after adding nodes");
        return;
      }
    }
  }


  // connect the nodes
  for (size_t i = 1; i < NumNodes; ++i) {
    bool cbError{false};
    graph.connectNodes(nodeIds[i - 1], 0, nodeIds[i], 0,
                       [&cbError](Status status, NodeId, size_t, NodeId, size_t) {
                         if (status != Status::Ok) {
                           cbError = true;
                         }
                       });
    // process and make sure everything got connected
    {
      const auto status = graph.process();

      if (status != Status::Ok || cbError) {
        state.SkipWithError("Error processing after connecting nodes");
        return;
      }
    }

  }

  for (auto _: state) {
    // push some data to the first node and process
    using MessageType = Message<DataType, TimeType>;
    MessageType msg;
    msg.data = '!';
    msg.time = 123.45f;
    auto status = firstNode->pushMessage(msg);
    if (status != Status::Ok) {
      state.SkipWithError("Failed to push message");
      return;
    }
    status = graph.process();
    if (status != Status::Ok) {
      state.SkipWithError("Process failed after pushing message");
      return;
    }
    MessageType msgOut;
    status = lastNode->popMessage(msgOut);
    if (status != Status::Ok) {
      state.SkipWithError("Failed to pop message");
      return;
    }
  }
}

BENCHMARK(Graph_Process_PassthroughChain<double, double, 64>);
