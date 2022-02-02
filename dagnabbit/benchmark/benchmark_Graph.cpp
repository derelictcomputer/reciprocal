#include <benchmark/benchmark.h>
#include "../Graph.h"
#include "../dev_helpers/PassthroughNode.h"

using namespace dc;

template<class TimeType, size_t MaxNodes>
static void Graph_AddRemoveAll(benchmark::State& state) {
  const auto createFn = []() { return new PassthroughNode<float, TimeType>(1, 1); };

  std::vector<NodeId> nodeIds;
  nodeIds.reserve(MaxNodes);

  for (auto _ : state) {
    Graph<TimeType> graph(MaxNodes, MaxNodes);
    nodeIds.clear();
    {
      std::atomic<size_t> cbCount{0};
      std::atomic<bool> error{false};
      const auto cb = [&cbCount, &error, &nodeIds](Status status, NodeId nodeId) {
        if (status != Status::Ok) {
          error = true;
        }
        ++cbCount;
        nodeIds.push_back(nodeId);
      };

      // add the nodes
      for (size_t i = 0; i < MaxNodes; ++i) {
        if (graph.addNode(createFn, cb) != Status::Ok) {
          state.SkipWithError("Failed to add node.");
          return;
        }
      }

      // process, which will flush the async queue
      const auto status = graph.process();
      if (status != Status::Ok) {
        state.SkipWithError("Process failed after add");
        return;
      }
      if (error) {
        state.SkipWithError("Error in callback after add.");
        return;
      }
      if (cbCount < MaxNodes) {
        state.SkipWithError("Received too few callbacks after add.");
        return;
      }
      if (graph.size() < MaxNodes) {
        state.SkipWithError("Too few nodes in graph after add.");
        return;
      }
    }

    {
      std::atomic<size_t> cbCount{0};
      std::atomic<bool> error{false};
      const auto cb = [&cbCount, &error](Status status, NodeId) {
        if (status != Status::Ok) {
          error = true;
        }
        ++cbCount;
      };

      // remove all the nodes
      for (auto id: nodeIds) {
        if (graph.removeNode(id, cb) != Status::Ok) {
          state.SkipWithError("Failed to remove node.");
          return;
        }
      }

      // process, which will flush the async queue
      const auto status = graph.process();
      if (status != Status::Ok || error || cbCount < MaxNodes || graph.size() != 0) {
        state.SkipWithError("Error during process after remove.");
        return;
      }
    }
  }
}

BENCHMARK(Graph_AddRemoveAll<int32_t, 64>);

template<class DataType, class TimeType, size_t MaxOutputConnections>
static void Graph_ConnectDisconnect(benchmark::State& state) {
  const auto createFn = []() { return new PassthroughNode<DataType, TimeType>(1, MaxOutputConnections); };

  std::vector<NodeId> nodeIds;
  nodeIds.reserve(MaxOutputConnections);

  for (auto _: state) {
    Graph<TimeType> graph(MaxOutputConnections + 1, MaxOutputConnections + 1);
    nodeIds.clear();

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

    // create a bunch of nodes to connect to the source
    for (size_t i = 0; i < MaxOutputConnections; ++i) {
      status = graph.addNode(createFn, [&cbError, &nodeIds](Status status, NodeId nodeId) {
        if (status != Status::Ok) {
          cbError = true;
        }
        nodeIds.push_back(nodeId);
      });
      if (status != Status::Ok) {
        state.SkipWithError("Failed to create destination node.");
        return;
      }
    }

    // process and make sure everything got created
    status = graph.process();

    if (status != Status::Ok || cbError || sourceNode == InvalidNodeId || nodeIds.size() != MaxOutputConnections) {
      state.SkipWithError("Error processing after adding nodes");
      return;
    }

    // connect all the destination nodes
    for (auto dest: nodeIds) {
      status = graph.connectNodes(sourceNode, 0, dest, 0, [&cbError](
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

    // process
    status = graph.process();

    if (status != Status::Ok || cbError) {
      state.SkipWithError("Error processing after connecting nodes");
      return;
    }

    // disconnect all the destination nodes
    for (auto dest: nodeIds) {
      status = graph.disconnectNodes(sourceNode, 0, dest, 0, [&cbError](
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

    // process
    status = graph.process();

    if (status != Status::Ok || cbError) {
      state.SkipWithError("Error processing after disconnecting nodes");
      return;
    }
  }
}

BENCHMARK(Graph_ConnectDisconnect<double, double, 16>);
