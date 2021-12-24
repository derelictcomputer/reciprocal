#pragma once

#include <cstddef>
#include <cstdint>

namespace dc {
using MessageTypeId = uint16_t;
const MessageTypeId InvalidMessageTypeId = 0;

/// A container for some data to send around.
/// Users of the library can extend this by adding new typeIds and codecs.
template<class DataType, size_t DataSize>
struct Message {
  /// The type id. This can be any value, and it's up to the user to know how to encode and decode it.
  /// Some helpers are included here for types we use within the library.
  MessageTypeId typeId{InvalidMessageTypeId};

  /// The data. Its meaning is user-defined.
  DataType data[DataSize];

  /// The number of blocks, in case for some reason we don't already know it.
  const size_t dataSize = DataSize;
};
}
