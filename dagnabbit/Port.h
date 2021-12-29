#pragma once

#include <cstdint>
#include <string>
#include "../core/SPSCQ.h"
#include "Message.h"

namespace dc {
using PortTypeId = uint16_t;
const PortTypeId InvalidPortType = -1;

template<class DataType, size_t DataSize, class TimeType, PortTypeId TypeId = InvalidPortType>
struct Port {
  /// The type of port, which will determine what can connect to it.
  const PortTypeId typeId{TypeId};

  /// The display name for the port.
  std::string prettyName;

  /// Convenience type for the messages this port uses
  using MessageType = Message<DataType, DataSize, TimeType>;

  /// The queue of messages for the port.
  /// Only one thread should push into the queue, and only one thread should pop from it.
  SPSCQ<MessageType> messageQueue;

  explicit Port(size_t queueSize) : messageQueue(queueSize) {}
};
}
