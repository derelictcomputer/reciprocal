#include <benchmark/benchmark.h>
#include "../../third_party/rigtorp/MPMCQueue.h"
#include "../SPSCQ.h"

using namespace dc;

template<class T, size_t capacity>
static void SPSCQ_FillDrain(benchmark::State& state) {
  SPSCQ<T> q(capacity);

  for (auto _: state) {
    while (q.push([](T&) { return Status::Ok; }) == Status::Ok);
    while (q.pop([](T&) { return Status::Ok; }) == Status::Ok);
  }
}

BENCHMARK(SPSCQ_FillDrain<double, 512>);


template<class T, size_t capacity>
static void MPMCQ_FillDrain(benchmark::State& state) {
  rigtorp::MPMCQueue<T> q(capacity);

  for (auto _: state) {
    while (q.try_push(T()));
    T t;
    while (q.try_pop(t));
  }
}

BENCHMARK(MPMCQ_FillDrain<double, 512>);

