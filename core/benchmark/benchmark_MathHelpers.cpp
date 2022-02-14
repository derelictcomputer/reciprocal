#include <limits>
#include <benchmark/benchmark.h>
#include "../MathHelpers.h"

using namespace dc;

template<class T>
static void MathHelpers_NextPowerOfTwoIterative(benchmark::State& state) {
  const T numValues = 64;
  const T step = std::numeric_limits<T>::max() / numValues;
  for (auto _ : state) {
    for (T i = 0; i < numValues - 1; ++i) {
      benchmark::DoNotOptimize(nextPowerOfTwo(T(i * step)));
    }
  }
}

BENCHMARK(MathHelpers_NextPowerOfTwoIterative<uint8_t>);
BENCHMARK(MathHelpers_NextPowerOfTwoIterative<uint16_t>);
BENCHMARK(MathHelpers_NextPowerOfTwoIterative<uint32_t>);
BENCHMARK(MathHelpers_NextPowerOfTwoIterative<uint64_t>);
