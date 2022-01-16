#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include "Status.h"

namespace dc {
// Single producer, single consumer, bounded, realtime-safe, lock-free, wait-free queue.
template<class T>
class SPSCQ {
public:
  explicit SPSCQ(size_t capacity) : capacity(capacity), _data(new T[capacity]) {}

  /// The max size of the queue.
  const size_t capacity;

  /// The current number of items in the queue.
  size_t size() const {
    return _size.load();
  }

  using Writer = std::function<Status(T&)>;

  /// Add an item to the queue.
  /// @param writer The function to write the item in the queue.
  /// @returns Status::Ok on success, Status::Full if full, or appropriate error.
  Status push(Writer&& writer) {
    // we're full
    if (_size >= capacity) {
      return Status::Full;
    }

    // write the data
    const auto status = writer(_data[_tail]);
    if (status != Status::Ok) {
      return status;
    }

    // advance the write pointer and update the size
    _tail = (_tail + 1) % capacity;
    _size.fetch_add(1);

    return Status::Ok;
  }

  using Reader = std::function<Status(T&)>;

  /// Remove an item from the queue.
  /// @param reader The function to read the item in the queue.
  /// @returns Status::Ok on success, Status::Empty if empty, or appropriate error.
  Status pop(Reader&& reader) {
    // we're empty
    if (_size == 0) {
      return Status::Empty;
    }

    // read the data
    const auto status = reader(_data[_head]);
    if (status != Status::Ok) {
      return status;
    }

    // advance the read ponter and update the size
    _head = (_head + 1) % capacity;
    _size.fetch_sub(1);

    return Status::Ok;
  }

private:
  std::unique_ptr<T[]> _data;
  std::atomic<size_t> _size{0};
  size_t _head{0};
  size_t _tail{0};
};
}