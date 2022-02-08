#include <thread>
#include <benchmark/benchmark.h>
#include "../Graph.h"
#include "../dev_helpers/PassthroughNode.h"

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
