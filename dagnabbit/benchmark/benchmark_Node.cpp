#include <benchmark/benchmark.h>
#include "../dev_helpers/PassthroughNode.h"

using namespace dc;

template<class DataType, class TimeType, size_t MaxOutputConnections>
static void Node_Passthrough_ConnectDisconnect(benchmark::State& state) {
  using NodeType = PassthroughNode<DataType, TimeType>;
  NodeType sourceNode(1, MaxOutputConnections);
  std::vector<std::unique_ptr<NodeType>> destNodes;
  for (size_t i = 0; i < MaxOutputConnections; ++i) {
    destNodes.emplace_back(std::make_unique<NodeType>(1, 1));
  }

  for (auto _ : state) {
    for (size_t i = 0; i < MaxOutputConnections; ++i) {
      if (destNodes[i]->connectInput(sourceNode, 0, 0) != Status::Ok) {
        state.SkipWithError("Failed to connect node during benchmark");
        return;
      }
    }
    for (size_t i = 0; i < MaxOutputConnections; ++i) {
      if (destNodes[i]->disconnectInput(sourceNode, 0, 0) != Status::Ok) {
        state.SkipWithError("Failed to disconnect node during benchmark");
        return;
      }
    }
  }
}

BENCHMARK(Node_Passthrough_ConnectDisconnect<double, double, 16>);
