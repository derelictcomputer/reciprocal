#pragma once
#include <functional>
#include "Param.h"
#include "Port.h"
#include "Status.h"

namespace dc {
class Node {
public:
  struct ProcessCtx {
    Param* params{nullptr};
    uint16_t numParams{0};
    Port* ports{nullptr};
    uint16_t numPorts{0};
    void* userData{nullptr};
  };

  using ProcessFn = std::function<Status(ProcessCtx)>;

  static Status passthroughProcessFn(ProcessCtx ctx) { return Status::Ok; }

  struct Config {
    Param* params{nullptr};
    uint16_t numParams{0};
    Port* ports{nullptr};
    uint16_t numPorts{0};
    ProcessFn processFn{passthroughProcessFn};
    void* userData{nullptr};
  };

  explicit Node(Config cfg);
  ~Node() = default;

  Status process();

protected:
  Config _cfg;
};
}
