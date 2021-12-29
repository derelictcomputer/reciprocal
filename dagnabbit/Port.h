#pragma once

#include <cstdint>
#include <string>
#include "../core/RTList.h"

namespace dc {
using PortTypeId = uint16_t;
const PortTypeId InvalidPortType = -1;

/// The mechanism by which messages travel between nodes.
struct Port {
  /// The type of port, which will determine what can connect to it.
  const PortTypeId typeId{InvalidPortType};

  /// The display name for the port.
  std::string prettyName;

  /// The other ports this one is connected to.
  RTList<Port*> connections;

  explicit Port(size_t maxConnections) : connections(maxConnections) {}
};
}
