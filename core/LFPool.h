#pragma once

#include <cassert>
#include <cstddef>
#include "../third_party/rigtorp/MPMCQueue.h"
#include "Status.h"

namespace dc {
/// Thread-safe, lock-free, realtime-safe pool of things.
/// For speed, does not keep track of borrowed items,
/// so the user is responsible for their lifecycle when outside the pool.
template<class T>
class LFPool {
public:
  template<class... Args>
  explicit LFPool(size_t capacity, Args&&... args) : _q(capacity) {
    for (size_t i = 0; i < capacity; ++i) {
      [[maybe_unused]] const auto success = _q.try_push(new T(std::forward<Args>(args)...));
      assert(success);
    }
  }

  ~LFPool() {
    while (!_q.empty()) {
      T* item{nullptr};
      [[maybe_unused]] const auto success = _q.try_pop(item);
      assert(success);
      assert(item != nullptr);
      delete item;
    }
  }

  /// Get an item from the pool.
  /// @param item The item, if there was one in the pool.
  /// @returns Status::Ok if there was an item in the pool, Status::Empty otherwise.
  Status acquire(T*& item) {
    return _q.try_pop(item) ? Status::Ok : Status::Empty;
  }

  /// Put an item back in the pool.
  /// @param item The item to put back.
  /// @returns Status::Ok if the item was put in the pool, Status::Full otherwise.
  Status release(T* item) {
    return _q.try_push(item) ? Status::Ok : Status::Full;
  }

private:
  rigtorp::MPMCQueue<T*> _q;
};
}
