#include "Node.h"
#include <utility>

using namespace dc;

Node::Node(Node::Config cfg) {
  _cfg = std::move(cfg);
}

Status Node::process() {
  if (_cfg.processFn == nullptr) {
    return Status::Fail;
  }
  return _cfg.processFn({_cfg.params, _cfg.ports, _cfg.userData});
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
