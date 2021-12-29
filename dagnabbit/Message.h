#pragma once

#include <cstddef>

namespace dc {
/// A container for some data to send around.
/// Users of the library can extend this by adding new typeIds and codecs.
template<class DataType, size_t DataSize, class TimeType>
struct Message {
  /// The data. Its meaning is user-defined.
  DataType data[DataSize];

  /// The number of blocks, in case for some reason we don't already know it.
  const size_t dataSize = DataSize;

  /// The time information, i.e. when did it happen?
  TimeType time;
};
}
