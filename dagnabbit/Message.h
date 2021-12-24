#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace dc {
using MessageTypeId = uint16_t;
const MessageTypeId InvalidMessageTypeId = 0;

/// A container for some data to send around.
/// Users of the library can extend this by adding new typeIds and codecs.
template<class DataType, size_t DataSize, class TimeType>
struct Message {
  /// The type id. This can be any value, and it's up to the user to know how to encode and decode it.
  /// Some helpers are included here for types we use within the library.
  MessageTypeId typeId{InvalidMessageTypeId};

  /// The data. Its meaning is user-defined.
  DataType data[DataSize];

  /// The number of blocks, in case for some reason we don't already know it.
  const size_t dataSize = DataSize;

  /// The time information, i.e. when did it happen?
  TimeType time;

  /// Just here for template constraints
  static constexpr bool isMessage() { return true; };
};

/// Allows constraining templates to specializations of Message (sort of, uggghhhhh)
template<class T>
concept MessageSpecialization = T::isMessage();
}
