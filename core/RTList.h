#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include "SPSCQ.h"
#include "Status.h"

namespace dc {
/// Realtime-safe (doesn't allocate/free aside from constructor/destructor) bounded linked list.
/// NOT thread safe.
template<class T>
class RTList {
public:
  using Writer = std::function<void(T&)>;
  using Comparer = std::function<bool(const T&)>;

  explicit RTList(size_t capacity) :
      _capacity(capacity),
      _head(new Item()),
      _pool(capacity) {
    for (size_t i = 0; i < _capacity; ++i) {
      _pool.push([](Item*& item) {
        item = new Item();
        return Status::Ok;
      });
    }
  }

  ~RTList() {
    // put everything back
    clear([](T&) {});

    // drain the pool
    while (_pool.pop([](Item*& item) {
      delete item;
      return Status::Ok;
    }) == Status::Ok);
  }

  /// Get the current size of the list.
  /// @returns The size of the list
  [[nodiscard]] size_t size() const {
    return _size;
  }

  /// Add an item to the list.
  /// @param writer The function to write to the item if added to the list.
  /// @returns Status::Ok or appropriate error.
  Status add(Writer&& writer) {
    // try to get an item from the pool
    const auto status = _pool.pop([this, &writer](Item*& item) {
      if (item == nullptr) {
        return Status::Fail;
      }

      // write to the item
      writer(item->data);

      // add it to the list
      Item* insertBehind = _head.get();
      while (insertBehind->next != nullptr) {
        insertBehind = insertBehind->next;
      }
      insertBehind->next = item;

      // increment size
      ++_size;

      return Status::Ok;
    });

    // pool empty means the list is full
    if (status == Status::Empty) {
      return Status::Full;
    }

    return status;
  }

  /// Iterate the items in the list.
  /// @param writer The function to frob each item in the list.
  /// @returns Status::Ok or appropriate error.
  Status iterate(Writer&& writer) {
    Item* item = _head->next;

    while (item != nullptr) {
      writer(item->data);
      item = item->next;
    }

    return Status::Ok;
  }

  /// Find the first item in the list that satisfies some requirement and frob it.
  /// @param comparer The function to determine whether this is the item we want to frob.
  /// @param writer The function that frobs the item if found.
  /// @returns Status::Ok or appropriate error.
  Status find(Comparer&& comparer, Writer&& writer) {
    Item* item = _head->next;

    while (item != nullptr) {
      // find the first item that satisfies comparer
      if (comparer(item->data)) {
        // read it and return
        writer(item->data);
        return Status::Ok;
      }

      // keep going
      item = item->next;
    }

    return Status::NotFound;
  }

  /// Remove the first item in the list that satisfies some requirement.
  /// @param comparer The function to determine whether we want to remove an item.
  /// @param writer The function to clear the item (if necessary).
  /// @returns Status::Ok or appropriate error.
  Status remove(Comparer&& comparer, Writer&& writer) {
    Item* prev = _head.get();

    while (prev->next != nullptr) {
      if (comparer(prev->next->data)) {
        // remove from the list
        Item* toRemove = prev->next;
        prev->next = toRemove->next;

        // decrement size
        --_size;

        // write to the item
        writer(toRemove->data);

        // put it back in the pool
        return _pool.push([&toRemove](Item*& item) {
          item = toRemove;
          return Status::Ok;
        });
      }

      // keep going
      prev = prev->next;
    }

    return Status::NotFound;
  }

  /// Remove all items in the list that satisfy some requirement.
  /// @param comparer The function to determine whether we want to remove an item.
  /// @param writer The function to clear the item (if necessary).
  /// @returns Status::Ok or appropriate error.
  Status removeAll(Comparer&& comparer, Writer&& writer) {
    Status status;

    do {
      status = remove(std::move(comparer), std::move(writer));
    } while (status == Status::Ok);

    return status == Status::NotFound ? Status::Ok : status;
  }

  /// Remove every item from the list.
  /// @param writer The function to clear each item (if necessary).
  /// @returns Status::Ok or appropriate error.
  Status clear(Writer&& writer) {
    while (_size > 0) {
      const auto status = remove(
          [](const T&) { return true; },
          [&writer](T& item) {
            writer(item);
          });
      if (status != Status::Ok) {
        return status;
      }
    }

    return Status::Ok;
  }

private:
  struct Item {
    T data;
    Item* next{nullptr};
  };

  const size_t _capacity;
  size_t _size{0};
  std::unique_ptr<Item> _head;
  SPSCQ<Item*> _pool;
};
}
