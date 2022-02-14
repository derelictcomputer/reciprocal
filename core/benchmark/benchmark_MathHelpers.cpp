#include <limits>
#include <benchmark/benchmark.h>
#include "../MathHelpers.h"

using namespace dc;

template<class T>
static void MathHelpers_NextPowerOfTwo(benchmark::State& state) {
  const T numValues = 64;
  const T step = std::numeric_limits<T>::max() / numValues;
  for (auto _ : state) {
    for (T i = 0; i < numValues - 1; ++i) {
      benchmark::DoNotOptimize(nextPowerOfTwo(T(i * step)));
    }
  }
}

BENCHMARK(MathHelpers_NextPowerOfTwo<uint8_t>);
BENCHMARK(MathHelpers_NextPowerOfTwo<uint16_t>);
BENCHMARK(MathHelpers_NextPowerOfTwo<uint32_t>);
BENCHMARK(MathHelpers_NextPowerOfTwo<uint64_t>);
