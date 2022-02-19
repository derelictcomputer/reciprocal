#include "Node.h"

using namespace dc;

Status NodeBase::connectInput(NodeBase& outputNode, size_t outputIndex, size_t inputIndex)  {
  if (&outputNode == this) {
    return Status::InvalidArgument;
  }

  if (outputIndex >= outputNode.getNumOutputs() || inputIndex >= getNumInputs()) {
    return Status::OutOfRange;
  }

  auto outputPort = outputNode._outputs[outputIndex].get();
  auto inputPort = _inputs[inputIndex].get();

  return outputPort->connect(inputPort);
}

Status NodeBase::disconnectInput(NodeBase& outputNode, size_t outputIndex, size_t inputIndex) {
  if (outputIndex >= outputNode.getNumOutputs() || inputIndex >= getNumInputs()) {
    return Status::OutOfRange;
  }

  auto outputPort = outputNode._outputs[outputIndex].get();
  auto inputPort = _inputs[inputIndex].get();

  return outputPort->disconnect(inputPort);
}


