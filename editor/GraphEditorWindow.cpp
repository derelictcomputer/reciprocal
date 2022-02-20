#include "imnodes.h"
#include "GraphEditorWindow.h"

using namespace dc;

GraphEditorWindow::GraphEditorWindow() {
  ImNodes::CreateContext();

  {
    NodeInfo i;
    i.name = "Node with input";
    _nodeIds.get(i.id);
    PortInfo p;
    p.name = "in";
    _portIds.get(p.id);
    i.inputPorts.emplace_back(std::move(p));
    _nodes.emplace_back(std::move(i));
  }
  {
    NodeInfo i;
    i.name = "Node with output";
    _nodeIds.get(i.id);
    PortInfo p;
    p.name = "out";
    _portIds.get(p.id);
    i.outputPorts.emplace_back(std::move(p));
    _nodes.emplace_back(std::move(i));
  }
}

GraphEditorWindow::~GraphEditorWindow() {
  ImNodes::DestroyContext();
}

Status GraphEditorWindow::draw() {
  ImGui::Begin("Graph Editor");
  {
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

    ImNodes::BeginNodeEditor();
    {
      for (const auto& node : _nodes) {
        NodeGUI::draw(node);
      }
    }
    ImNodes::EndNodeEditor();
  }
  ImGui::End();

  return Status::Ok;
}
