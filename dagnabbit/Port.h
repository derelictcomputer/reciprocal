#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "../core/Status.h"

namespace dc {
using PortTypeId = uint16_t;
const PortTypeId InvalidPortType = -1;

/// The mechanism by which messages travel between nodes.
class Port {
public:
  struct Config {
    PortTypeId typeId{InvalidPortType};
    std::string prettyName;
    size_t maxConnections{1};
    std::function<void*()> createMessageQueueFn{nullptr};
    std::function<void(void*)> destroyMessageQueueFn{nullptr};
  };

  explicit Port(const Config& cfg);

  ~Port();

  /// The type of port, which will determine what can connect to it.
  const PortTypeId typeId;

  /// The display name for the port.
  const std::string prettyName;

  /// The max number of connections allowed for this port
  const size_t maxConnections;

  /// The current number of other ports connected to this port
  /// @returns The number of connected ports.
  [[nodiscard]] size_t getNumConnections() const;

  /// Check whether this port is connected to the given port.
  /// @returns true if connected, otherwise false
  bool isConnectedTo(Port* other);

  /// Try to connect this port to another port.
  /// @param other The other port
  /// @returns Status::Ok or appropriate error.
  Status connect(Port* other);

  /// Try to disconnect this port from another port.
  /// @param other The other port
  /// @returns Status::Ok on successful disconnect. Status::NotFound if not connected.
  Status disconnect(Port* other);

  /// Disconnect all the connected ports.
  /// @returns Status::Ok or appropriate error
  Status disconnectAll();

  /// Get the message queue for this port if there is one.
  /// @param messageQueue A pointer to the message queue. It's up to the user to know what to cast it to.
  /// @returns Status::Ok if there is a message queue to get, Status::NotFound otherwise.
  Status getMessageQueue(void*& messageQueue);

  using Frobber = std::function<Status(Port*)>;

  /// Do something to all the connections.
  /// @param frobber Function to frobnicate the other ports.
  /// @returns Status::Ok or appropriate error. The user can force an error within their Frobber.
  Status frobConnections(Frobber&& frobber);

protected:
  std::vector<std::atomic<Port*>> _connections;

private:
  std::function<void(void*)> _destroyMessageQueueFn;

  void* _messageQueue{nullptr};
};
}
