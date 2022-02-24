#pragma once

#include "../core/Status.h"
#include "Port.h"

namespace dc {
/// A locally-unique id for a node in a graph.
using NodeId = size_t;
const NodeId InvalidNodeId = 0;

class NodeBase {
public:
  /// Get the number of input ports on this node.
  /// @returns The number of inputs.
  [[nodiscard]] size_t getNumInputs() const {
    return _inputs.size();
  }

  /// Get the number of output ports on this node.
  /// @returns The number of outputs.
  [[nodiscard]] size_t getNumOutputs() const {
    return _outputs.size();
  }

  /// Connect the output of another node to an input of this one.
  /// @param outputNode The other node
  /// @param outputIndex The index of the output port from the other node
  /// @param inputIndex The index of the input port from this node
  /// @returns Status::Ok or appropriate error.
  Status connectInput(NodeBase& outputNode, size_t outputIndex, size_t inputIndex);

  /// Disconnect another node's output from an input on this one.
  /// @param outputNode The other node
  /// @param outputIndex The index of the output port from the other node
  /// @param inputIndex The index of the input port from this node
  /// @returns Status::Ok or appropriate error.
  Status disconnectInput(NodeBase& outputNode, size_t outputIndex, size_t inputIndex);

  /// Reset the node's internal state.
  virtual void reset() {}

protected:
  template<class MessageType>
  void addInputPort(std::string&& prettyName, size_t queueSize) {
    _inputs.emplace_back(std::make_unique<InputPort<MessageType>>(this, std::move(prettyName), queueSize));
  }

  template<class MessageType>
  Status pushInputMessage(size_t portIndex, const MessageType& msg) {
    if (portIndex >= _inputs.size()) {
      return Status::OutOfRange;
    }
    auto p = static_cast<InputPort<MessageType>*>(_inputs[portIndex].get());
    return p->pushMessage(msg);
  }

  template<class MessageType>
  Status popInputMessage(size_t portIndex, MessageType& msg) {
    if (portIndex >= _inputs.size()) {
      return Status::OutOfRange;
    }
    auto p = static_cast<InputPort<MessageType>*>(_inputs[portIndex].get());
    return p->popMessage(msg);
  }

  template<class MessageType>
  void addOutputPort(std::string&& prettyName, size_t maxConnections) {
    _outputs.emplace_back(std::make_unique<OutputPort<MessageType>>(this, std::move(prettyName), maxConnections));
  }

  Status getNumOutputConnections(size_t portIndex, size_t& numConnections) {
    if (portIndex >= _outputs.size()) {
      return Status::OutOfRange;
    }
    numConnections = _outputs[portIndex]->getNumConnections();
    return Status::Ok;
  }

  template<class MessageType>
  Status pushOutputMessage(size_t portIndex, const MessageType& msg) {
    if (portIndex >= _outputs.size()) {
      return Status::OutOfRange;
    }

    auto p = static_cast<OutputPort<MessageType>*>(_outputs[portIndex].get());

    if (p->getNumConnections() == 0) {
      return Status::NoConnection;
    }

    return p->pushToConnections(msg);
  }



private:
  // Let the owning graph look at ports/connections
  // so we don't have to write a complicated API for topological sorting.
  template<class TimeType> friend
  class Graph;

  // Used by the Graph to sort nodes
  bool _visited;
  NodeId _id{InvalidNodeId};

  std::vector<std::unique_ptr<PortBase>> _inputs;
  std::vector<std::unique_ptr<PortBase>> _outputs;
};

template<class TimeType>
class Node : public NodeBase {
public:
  virtual ~Node() = default;

  /// Advance the node, using input and passing output as applicable.
  /// @param now The absolute time based on the owning graph.
  /// @returns Status::Ok on success or appropriate error.
  virtual Status process(const TimeType& now, const TimeType& deltaTime) = 0;
};
}
