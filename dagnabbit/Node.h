#pragma once

#include "../core/Status.h"
#include "Port.h"

namespace dc {
template<class TimeType>
class Node {
public:
  /// Advance the node, using input and passing output as applicable.
  /// @param now The absolute time based on the owning graph.
  /// @returns Status::Ok on success or appropriate error.
  virtual Status process(const TimeType& now, const TimeType& deltaTime) = 0;

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
  Status connectInput(Node<TimeType>& outputNode, size_t outputIndex, size_t inputIndex) {
    if (outputIndex >= outputNode.getNumOutputs() || inputIndex >= getNumInputs()) {
      return Status::OutOfRange;
    }

    auto outputPort = outputNode._outputs[outputIndex];
    auto inputPort = _inputs[inputIndex];

    return outputPort->connect(inputPort);
  }

protected:
  // IMPORTANT: Initialize ports in your Node's constructor and don't reconfigure after that.
  // The base class does not clean up ports, in case it makes things simpler for you, so they're your responsibility.
  std::vector<IPort*> _inputs;
  std::vector<IPort*> _outputs;
};
}
