#include <vector>
#include <benchmark/benchmark.h>
#include "../LFPool.h"

using namespace dc;

static void LFPool_AcquireReleaseAll(benchmark::State& state) {
  const size_t poolSize = 2048;
  LFPool<int> pool(poolSize);

  std::vector<int*> acquired;
  acquired.reserve(poolSize);

  for (auto _ : state) {
    int* iPtr{nullptr};
    for (size_t i = 0; i < poolSize; ++i) {
      pool.acquire(iPtr);
      acquired.push_back(iPtr);
    }
    for (size_t i = 0; i < poolSize; ++i) {
      pool.release(acquired[i]);
    }
  }
}

BENCHMARK(LFPool_AcquireReleaseAll);
