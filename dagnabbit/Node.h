#pragma once
#include <functional>
#include <vector>
#include "Param.h"
#include "Port.h"
#include "Status.h"

namespace dc {
class Node {
public:
  using ProcessFn = std::function<Status(Node& node)>;

  static Status passthroughProcessFn(Node& node) { return Status::Ok; }

  struct Config {
    std::vector<Param> params;
    std::vector<Port> ports;
    ProcessFn processFn{passthroughProcessFn};
  };

  explicit Node(Config cfg);
  ~Node() = default;

  Status process();

  Status setParam(size_t paramIdx, float value);
  Status getParam(size_t paramIdx, float& value) const;
  size_t numParams() const { return _cfg.params.size(); }

protected:
  Config _cfg;
};
}
