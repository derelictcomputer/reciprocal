#pragma once

#include "../core/Status.h"
#include "Port.h"

namespace dc {
template<class TimeType>
class Node {
public:
  virtual Status process(const TimeType& now, const TimeType& deltaTime) = 0;

  [[nodiscard]] size_t getNumInputs() const {
    return _inputs.size();
  }

  [[nodiscard]] size_t getNumOutputs() const {
    return _inputs.size();
  }

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
