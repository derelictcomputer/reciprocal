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
      for (const auto& node: _nodes) {
        NodeGUI::draw(node);
      }
      for (const auto& connection: _connections) {
        ImNodes::Link(connection.id, connection.sourcePortId, connection.destPortId);
      }
    }
    ImNodes::EndNodeEditor();

    Connection connection;
    if (ImNodes::IsLinkCreated(&connection.sourceNodeId,
                               &connection.sourcePortId,
                               &connection.destNodeId,
                               &connection.destPortId)) {
      _connectionIds.get(connection.id);
      _connections.emplace_back(connection);
    }
  }
  ImGui::End();

  return Status::Ok;
}
