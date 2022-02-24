#pragma once

#include <cstddef>
#include <vector>
#include "Status.h"

namespace dc {
/// A Locally Unique IDentifier, for when you need something to be unique to a particular scope.
/// @tparam T The type for the ids, must be integral
/// @tparam MaxSize (optional) The max size if you don't want LUID to allocate memory. Zero will allocate as needed.
template<class T, size_t MaxSize = 0> requires std::is_integral_v<T>
class LUID {
public:
  static_assert(
      MaxSize < static_cast<size_t>(std::numeric_limits<T>::max()) - std::numeric_limits<T>::lowest(),
      "MaxSize must be less than the range of the id type."
  );

  LUID() : maxSize(MaxSize) {
    _nextId = std::numeric_limits<T>::lowest();
    if (maxSize > 0) {
      _availableIds.reserve(maxSize);
      for (size_t i = 0; i < maxSize; ++i) {
        _availableIds.push_back(_nextId++);
      }
    }
  }

  /// The max number of ids, if desired.
  const size_t maxSize;

  /// Get an id
  /// @param id The id, if successful
  /// @returns Status::Ok or appropriate error
  Status get(T& id) {
    if (maxSize > 0) {
      if (_availableIds.empty()) {
        return Status::Empty;
      }

      id = _availableIds[_availableIds.size() - 1];
      _availableIds.pop_back();
      return Status::Ok;
    }

    if (_availableIds.empty()) {
      id = _nextId++;
      return Status::Ok;
    }

    id = _availableIds[_availableIds.size() - 1];
    _availableIds.pop_back();
    return Status::Ok;
  }

  /// Replace an id
  /// @param id The id
  /// @returns Status::Ok or appropriate error
  Status replace(T id) {
    // paranoid check to make sure we're not trying to put back an id we already have
    for (auto aId : _availableIds) {
      if (aId == id) {
        return Status::Duplicate;
      }
    }

    if (maxSize > 0) {
      if (_availableIds.size() == maxSize) {
        return Status::Full;
      }

      _availableIds.push_back(id);
      return Status::Ok;
    }

    _availableIds.push_back(id);
    return Status::Ok;
  }

private:
  std::vector<T> _availableIds;
  T _nextId;
};
}
