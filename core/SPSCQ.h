#pragma once

#include <atomic>
#include <memory>
#include "MathHelpers.h"
#include "Status.h"

namespace dc {
// Single producer, single consumer, bounded, realtime-safe, lock-free, wait-free queue.
template<class T>
class SPSCQ {
public:
  explicit SPSCQ(size_t capacity) : capacity(nextPowerOfTwo(capacity)), _data(new T[this->capacity]) {}

  constexpr size_t mod(size_t i) {
    return i & (capacity - 1);
  }

  /// The max size of the queue.
  const size_t capacity;

  /// The current number of items in the queue.
  size_t size() const {
    return _size.load();
  }

  /// Add an item to the queue.
  /// @param item The thing to push
  /// @returns Status::Ok on success, Status::Full if full, or appropriate error.
  Status push(const T& item) {
    // we're full
    if (_size.load(std::memory_order::acquire) >= capacity) {
      return Status::Full;
    }
    _data[_tail] = item;
    _tail = mod(++_tail);
    _size.fetch_add(1, std::memory_order::release);
    return Status::Ok;
  }

  /// Remove an item from the queue.
  /// @param item The thing to pop
  /// @returns Status::Ok on success, Status::Empty if empty, or appropriate error.
  Status pop(T& item) {
    // we're empty
    if (_size.load(std::memory_order::acquire) == 0) {
      return Status::Empty;
    }
    item = _data[_head];
    _head = mod(++_head);
    _size.fetch_sub(1, std::memory_order::release);
    return Status::Ok;
  }

private:
  std::unique_ptr<T[]> _data;
  std::atomic<size_t> _size{0};
  size_t _head{0};
  size_t _tail{0};
};
}