#include <benchmark/benchmark.h>
#include "../TrashMan.h"

using namespace dc;

template<class T, size_t capacity>
static void TrashMan_FillEmpty(benchmark::State& state) {
  for (auto _ : state) {
    TrashMan<T> trashMan(capacity);
    // fill the trash
    for (size_t i = 0; i < capacity; ++i) {
      T* thing = new T();
      if (trashMan.trash(thing) != Status::Ok) {
        state.SkipWithError("Failed to trash a thing.");
        return;
      }
    }
    trashMan.dump();
  }
}

BENCHMARK(TrashMan_FillEmpty<int, 512>);
