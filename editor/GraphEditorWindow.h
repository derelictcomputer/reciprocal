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

  std::vector<NodeInfo> _nodes;
};
}
