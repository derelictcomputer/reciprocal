#pragma once

#include <thread>
#include "../third_party/rigtorp/MPMCQueue.h"
#include "Status.h"

namespace dc {
/// Use this to offload deleting things to another thread. Kill Em All 1989.
/// @tparam T The type of the thing you want deleted on the other thread.
template<class T>
class TrashMan {
public:
  explicit TrashMan(size_t capacity) : capacity(capacity), _trashCan(capacity) {}

  ~TrashMan() {
    dump();
  }

  const size_t capacity;

  /// @returns The number of things in the trash can. TBH, this isn't very useful except for tests.
  [[nodiscard]] size_t size() const {
    return _trashCan.size();
  }

  /// Put something in the trash.
  /// @param thing The thing to trash. Will be set to nullptr if successful.
  /// @returns Status::Ok on success or appropriate error.
  Status trash(T*& thing) {
    if (thing == nullptr) {
      return Status::InvalidArgument;
    }

    if (!_trashCan.try_push(thing)) {
      return Status::Full;
    }

    thing = nullptr;
    return Status::Ok;
  }

  void dump() {
    T* ptr{nullptr};
    while (!_trashCan.empty()) {
      if (_trashCan.try_pop(ptr)) {
        assert(ptr != nullptr);
        delete ptr;
        ptr = nullptr;
      }
    }
  }

private:
  rigtorp::MPMCQueue<T*> _trashCan;
};
}
