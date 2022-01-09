#pragma once

#include <cstddef>

namespace dc {
/// A container for some data to send around.
/// Users of the library can extend this by adding new typeIds and codecs.
template<class DataType, class TimeType>
struct Message {
  /// The data. Its meaning is user-defined.
  DataType data{DataType()};

  /// The time information, i.e. when did it happen?
  TimeType time{TimeType()};
};
}
