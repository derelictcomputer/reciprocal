#pragma once

#include <string>
#include <vector>
#include "core/Status.h"

namespace dc {
struct PortInfo {
  std::string name;
  int id;
};

struct NodeInfo {
  std::string name;
  int id;
  std::vector<PortInfo> inputPorts;
  std::vector<PortInfo> outputPorts;
};

namespace NodeGUI {
  Status draw(const NodeInfo& info);
}
}
