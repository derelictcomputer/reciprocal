#pragma once

#include "core/LUID.h"
#include "NodeGUI.h"

namespace dc {
class GraphEditorWindow {
public:
  GraphEditorWindow();

  ~GraphEditorWindow();

  Status draw();

private:
  LUID<int> _nodeIds;
  LUID<int> _portIds;
  LUID<int> _connectionIds;

  std::vector<NodeInfo> _nodes;

  struct Connection {
    int id{0};
    int sourceNodeId{0};
    int sourcePortId{0};
    int destNodeId{0};
    int destPortId{0};
  };

  std::vector<Connection> _connections;
};
}
