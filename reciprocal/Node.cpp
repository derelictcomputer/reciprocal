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
  return _cfg.processFn({_cfg.params, _cfg.numParams, _cfg.ports, _cfg.numPorts, _cfg.userData});
}
