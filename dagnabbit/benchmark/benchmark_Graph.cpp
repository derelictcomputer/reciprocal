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
