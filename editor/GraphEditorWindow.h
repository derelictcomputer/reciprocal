#pragma once

#include "core/Status.h"

namespace dc {
class GraphEditorWindow {
public:
  GraphEditorWindow();

  ~GraphEditorWindow();

  Status draw();
};
}
