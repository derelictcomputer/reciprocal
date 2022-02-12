#include <benchmark/benchmark.h>
#include "dagnabbit/PassthroughNode.h"

using namespace dc;

template<class DataType, class TimeType>
static void Node_Passthrough_ConnectDisconnect(benchmark::State& state) {
  using NodeType = PassthroughNode<DataType, TimeType>;
  NodeType sourceNode(1, 1);
  NodeType destNode(1, 1);

  for (auto _: state) {
    if (destNode.connectInput(sourceNode, 0, 0) != Status::Ok) {
      state.SkipWithError("Failed to connect node during benchmark");
      return;
    }
    if (destNode.disconnectInput(sourceNode, 0, 0) != Status::Ok) {
      state.SkipWithError("Failed to connect node during benchmark");
      return;
    }
  }
}

BENCHMARK(Node_Passthrough_ConnectDisconnect<double, double>);
