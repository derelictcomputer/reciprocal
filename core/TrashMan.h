#pragma once

#include <condition_variable>
#include <thread>
#include "SPSCQ.h"

namespace dc {
/// Use this to offload deleting things from a single realtime thread. Kill Em All 1989.
/// @tparam T The type of the thing you want deleted on the cleanup thread.
template<class T>
class TrashMan {
public:
  explicit TrashMan(size_t capacity) : _trashCan(capacity), _trashThread([this]() {
    std::unique_lock<std::mutex> lock(_mutex);

    while (_run.load()) {
      // wait for a signal
      _dump.wait(lock);

      // dump the trash
      while (_trashCan.pop([](T*& trash) {
        delete trash;
        trash = nullptr;
        return Status::Ok;
      }) == Status::Ok);
    }
  }) {}

  ~TrashMan() {
    // tell the trash thread to dump and then stop running. Order is important here.
    _run = false;
    _dump.notify_one();
    _trashThread.join();
  }

  /// @returns The size of the trash can.
  [[nodiscard]] size_t capacity() const {
    return _trashCan.capacity;
  }

  /// @returns The number of things in the trash can. TBH, this isn't very useful except for tests.
  [[nodiscard]] size_t size() const {
    return _trashCan.size();
  }

  /// Put something in the trash.
  /// @param thing The thing to trash. Will be set to nullptr if successful.
  /// @returns Status::Ok on success, Status::Full if the trash is full.
  Status trash(T*& thing) {
    const auto status = _trashCan.push([thing](T*& item) {
      item = thing;
      return Status::Ok;
    });
    if (status != Status::Ok) {
      return status;
    }
    thing = nullptr;
    _dump.notify_one();
    return Status::Ok;
  }

private:
  SPSCQ<T*> _trashCan;
  std::atomic<bool> _run{true};
  std::condition_variable _dump;
  std::mutex _mutex;
  std::thread _trashThread;
};
}
