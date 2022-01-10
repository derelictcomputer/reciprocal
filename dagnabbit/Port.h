#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include "../core/Status.h"
#include "../third_party/rigtorp/MPMCQueue.h"

namespace dc {
/// The mechanism by which messages travel between nodes.
class IPort {
public:
  explicit IPort(std::string prettyName, size_t maxConnections, size_t typeId, size_t canConnectToTypeId);

  // This is just here to make it so no one can instantiate this interface
  virtual ~IPort() = 0;

  /// Unique id for this port's type.
  const size_t typeId;

  /// Unique id for the type of port that can connect to this one.
  const size_t canConnectToTypeId;

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
class OutputPort;

/// An input into a node. Restricted to 1 connection and has a queue to manage messages.
template<class MessageType>
class InputPort : public IPort {
public:
  using QueueType = rigtorp::MPMCQueue<MessageType>;

  explicit InputPort(const std::string& prettyName, size_t queueSize) :
      IPort(prettyName, 
            1,
            typeid(InputPort<MessageType>).hash_code(),
            typeid(OutputPort<MessageType>).hash_code()),
      _q(queueSize) {
  }

  /// Add a message to the queue.
  /// @param msg The message
  /// @returns Status::Ok on success, Status::Full if the queue was full
  Status pushMessage(const MessageType& msg) {
    return _q.try_push(msg) ? Status::Ok : Status::Full;
  }

  /// Get a message from the queue.
  /// @param msg The message, if there was one in the queue.
  /// @returns Status::Ok on success, Status::Empty if the queue was empty
  Status popMessage(MessageType& msg) {
    return _q.try_pop(msg) ? Status::Ok : Status::Empty;
  }

private:
  QueueType _q;
};

/// An output from a node. Can have more than one connection if desired.
template<class MessageType>
class OutputPort : public IPort {
public:
  explicit OutputPort(const std::string& prettyName, size_t maxConnections) :
      IPort(prettyName,
            maxConnections,
            typeid(OutputPort<MessageType>).hash_code(),
            typeid(InputPort<MessageType>).hash_code()) {
  }

  /// Add a message to the queue for all input nodes connected to this one.
  /// @param msg The message
  /// @returns Status::Ok or appropriate error.
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
