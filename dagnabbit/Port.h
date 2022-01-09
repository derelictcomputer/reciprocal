#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <string>
#include "../core/Status.h"
#include "../third_party/rigtorp/MPMCQueue.h"

namespace dc {
using PortTypeId = uint16_t;
const PortTypeId InvalidPortType = -1;

/// The mechanism by which messages travel between nodes.
class IPort {
public:
  struct Config {
    PortTypeId typeId{InvalidPortType};
    std::string prettyName;
    size_t maxConnections{1};
  };

  explicit IPort(const Config& cfg);

  virtual ~IPort() = default;

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
  bool isConnectedTo(IPort* other);

  /// Try to connect this port to another port.
  /// @param other The other port
  /// @returns Status::Ok or appropriate error.
  Status connect(IPort* other);

  /// Try to disconnect this port from another port.
  /// @param other The other port
  /// @returns Status::Ok on successful disconnect. Status::NotFound if not connected.
  Status disconnect(IPort* other);

  /// Disconnect all the connected ports.
  /// @returns Status::Ok or appropriate error
  Status disconnectAll();

protected:
  std::unique_ptr<std::atomic<IPort*>[]> _connections;
};

template<class MessageType>
class InputPort : public IPort {
public:
  using QueueType = rigtorp::MPMCQueue<MessageType>;

  explicit InputPort(const IPort::Config& cfg, size_t queueSize) : IPort(cfg), _q(queueSize) {}

  Status pushMessage(const MessageType& msg) {
    return _q.try_push(msg) ? Status::Ok : Status::Full;
  }

  Status popMessage(MessageType& msg) {
    return _q.try_pop(msg) ? Status::Ok : Status::Empty;
  }

private:
  QueueType _q;
};

template<class MessageType>
class OutputPort : public IPort {
public:
  explicit OutputPort(const IPort::Config& cfg) : IPort(cfg) {}

  Status pushToConnections(const MessageType& msg) {
    for (size_t i = 0; i < maxConnections; ++i) {
      auto& c = _connections[i];
      auto other = dynamic_cast<InputPort<MessageType>*>(c.load());
      if (other != nullptr) {
        const auto status = other->pushMessage(msg);
        if (status != Status::Ok) {
          return status;
        }
      }
    }

    return Status::Ok;
  }
};
}
