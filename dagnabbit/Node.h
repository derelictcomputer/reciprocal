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

    auto outputPort = outputNode._outputs[outputIndex].get();
    auto inputPort = _inputs[inputIndex].get();

    return outputPort->connect(inputPort);
  }

protected:
  // IMPORTANT: Initialize ports in your Node's constructor and don't reconfigure after that.
  std::vector<std::unique_ptr<IPort>> _inputs;
  std::vector<std::unique_ptr<IPort>> _outputs;
};
}
