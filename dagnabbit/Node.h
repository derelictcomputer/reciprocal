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

  static Status passthroughProcessFn(Node& node);

  struct Config {
    std::vector<Param> params;
    std::vector<Port> inputPorts;
    std::vector<Port> outputPorts;
    ProcessFn processFn{passthroughProcessFn};
  };

  enum class PortType : uint8_t  {
    Input = 0,
    Output,
    SIZE
  };

  explicit Node(Config cfg);
  ~Node() = default;

  Status process();

  Status setParam(size_t paramIdx, float value);
  Status getParam(size_t paramIdx, float& value) const;
  size_t numParams() const { return _cfg.params.size(); }

  Status getNumPorts(PortType type, size_t& numPorts) const;
  Status getPort(size_t portIdx, PortType type, Port*& port);

protected:
  Config _cfg;
};
}
