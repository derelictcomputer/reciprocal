#pragma once

#include <string>
#include <vector>
#include "../core/SPSCQ.h"

namespace dc {
class NodeBase;

/// The mechanism by which messages travel between nodes.
/// NOTE: Operations are not thread-safe.
class PortBase {
public:
  explicit PortBase(NodeBase* parent,
                    std::string&& prettyName,
                    size_t maxConnections,
                    size_t typeId,
                    size_t canConnectToTypeId);

  // This is just here to make it so no one can instantiate this interface
  virtual ~PortBase() = 0;

  /// A pointer to the port's node
  NodeBase* parent;

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

  /// Get the connection at the given index
  /// @param index The index of the connection you want
  /// @param connection The connection, if found
  /// @returns Status::Ok or appropriate error
  Status getConnection(size_t index, PortBase*& connection);

  /// Check whether this port is connected to the given port.
  /// @returns true if connected, otherwise false
  bool isConnectedTo(PortBase* other);

  /// Try to connect this port to another port.
  /// @param other The other port
  /// @returns Status::Ok or appropriate error.
  Status connect(PortBase* other);

  /// Try to disconnect this port from another port.
  /// @param other The other port
  /// @returns Status::Ok on successful disconnect. Status::NotFound if not connected.
  Status disconnect(PortBase* other);

  /// Disconnect all the connected ports.
  /// @returns Status::Ok or appropriate error
  Status disconnectAll();

protected:
  std::vector<PortBase*> _connections;
};

template<class MessageType>
class OutputPort;

/// An input into a node. Restricted to 1 connection and has a queue to manage messages.
/// NOTE: Operations are not thread-safe.
template<class MessageType>
class InputPort : public PortBase {
public:
  using QueueType = SPSCQ<MessageType>;

  explicit InputPort(NodeBase* parent, std::string&& prettyName, size_t queueSize) :
      PortBase(parent,
               std::move(prettyName),
               1,
               typeid(InputPort<MessageType>).hash_code(),
               typeid(OutputPort<MessageType>).hash_code()),
      _q(queueSize) {}

  /// Add a message to the queue.
  /// @param msg The message
  /// @returns Status::Ok on success, Status::Full if the queue was full
  Status pushMessage(const MessageType& msg) {
    return _q.push(msg);
  }

  /// Get a message from the queue.
  /// @param msg The message, if there was one in the queue.
  /// @returns Status::Ok on success, Status::Empty if the queue was empty
  Status popMessage(MessageType& msg) {
    return _q.pop(msg);
  }

private:
  QueueType _q;
};

/// An output from a node. Can have more than one connection if desired.
/// NOTE: Operations are not thread-safe.
template<class MessageType>
class OutputPort : public PortBase {
public:
  explicit OutputPort(NodeBase* parent, std::string&& prettyName, size_t maxConnections) :
      PortBase(parent,
               std::move(prettyName),
               maxConnections,
               typeid(OutputPort<MessageType>).hash_code(),
               typeid(InputPort<MessageType>).hash_code()) {
  }

  /// Add a message to the queue for all input nodes connected to this one.
  /// @param msg The message
  /// @returns Status::Ok or appropriate error.
  Status pushToConnections(const MessageType& msg) {
    for (auto c: _connections) {
      auto inPort = static_cast<InputPort<MessageType>*>(c);
      const auto status = inPort->pushMessage(msg);
      if (status != Status::Ok) {
        return status;
      }
    }

    return Status::Ok;
  }
};
}
