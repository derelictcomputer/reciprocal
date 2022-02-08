#pragma once

#include "../core/Status.h"
#include "Port.h"

namespace dc {
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
    return _inputs.size();
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

protected:
  std::vector<PortBase*> _inputs;
  std::vector<PortBase*> _outputs;
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
