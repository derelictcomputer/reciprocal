#include <benchmark/benchmark.h>
#include "../SPSCQ.h"

using namespace dc;

template<class T, size_t capacity>
static void BM_PushPop(benchmark::State& state) {
  SPSCQ<T> q(capacity);

  for (auto _ : state) {
    q.push([](T&) {
      return Status::Ok;
    });
    q.pop([](T&) {
      return Status::Ok;
    });
  }
}
BENCHMARK(BM_PushPop<int, 64>);
BENCHMARK(BM_PushPop<double, 512>);
BENCHMARK(BM_PushPop<float, 128>);

template<class T, size_t capacity>
static void BM_FillDrain(benchmark::State& state) {
  SPSCQ<T> q(capacity);

  for (auto _ : state) {
    while (q.size() < capacity) {
      q.push([](T&) { return Status::Ok; });
    }
    while (q.size() > 0) {
      q.pop([](T&) { return Status::Ok; });
    }
  }
}
BENCHMARK(BM_FillDrain<int, 64>);
BENCHMARK(BM_FillDrain<double, 512>);
BENCHMARK(BM_FillDrain<float, 128>);

BENCHMARK_MAIN();
