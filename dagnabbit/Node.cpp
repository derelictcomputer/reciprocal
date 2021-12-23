#include "Node.h"
#include <utility>

using namespace dc;

Status Node::passthroughProcessFn(Node &node) {
  // number of in and out ports must match, so we can do a generic passthrough
  if (node._cfg.inputPorts.size() != node._cfg.outputPorts.size()) {
    return Status::Mismatch;
  }

  // pass each input through to the corresponding output
  for (size_t i = 0; i < node._cfg.inputPorts.size(); ++i) {
    auto& inPort = node._cfg.inputPorts[i];
    auto& outPort = node._cfg.outputPorts[i];

    // number of channels and samples must match
    if (inPort.numChannels != outPort.numChannels || inPort.numSamples != outPort.numSamples) {
      return Status::Mismatch;
    }

    // instead of copying the buffer, just assign the data pointer from the input to the output
    outPort.data = inPort.data;
  }

  return Status::Ok;
}

Node::Node(Node::Config cfg) {
  _cfg = std::move(cfg);
}

Status Node::process() {
  if (_cfg.processFn == nullptr) {
    return Status::Fail;
  }
  return _cfg.processFn(*this);
}

Status Node::setParam(size_t paramIdx, float value) {
  if (paramIdx < numParams()) {
    return _cfg.params[paramIdx].set(value);
  }
  return Status::OutOfRange;
}

Status Node::getParam(size_t paramIdx, float &value) const {
  if (paramIdx < numParams()) {
    return _cfg.params[paramIdx].get(value);
  }
  return Status::OutOfRange;
}

Status Node::getNumPorts(Node::PortType type, size_t &numPorts) const {
  switch (type) {
    case PortType::Input:
      numPorts = _cfg.inputPorts.size();
      return Status::Ok;
    case PortType::Output:
      numPorts = _cfg.outputPorts.size();
      return Status::Ok;
    case PortType::SIZE:
      return Status::OutOfRange;
  }

  // unhandled
  return Status::Fail;
}

Status Node::getPort(size_t portIdx, Node::PortType type, Port *&port) {
  switch (type) {
    case PortType::Input:
      if (portIdx >= _cfg.inputPorts.size()) {
        return Status::OutOfRange;
      }
      port = &_cfg.inputPorts[portIdx];
      return Status::Ok;
    case PortType::Output:
      if (portIdx >= _cfg.outputPorts.size()) {
        return Status::OutOfRange;
      }
      port = &_cfg.outputPorts[portIdx];
      return Status::Ok;
    case PortType::SIZE:
      return Status::OutOfRange;
  }

  // unhandled
  return Status::Fail;
}
