#include "imnodes.h"
#include "GraphEditorWindow.h"

using namespace dc;

struct PortDef {
  std::string name;
};

struct NodeDef {
  std::string name;
  std::vector<PortDef> inputPorts;
  std::vector<PortDef> outputPorts;
};

NodeDef NodeWithInput{
  "Node with input",
  {{"in"}},
  {}
};

NodeDef NodeWithOutput {
  "Node with output",
  {},
  {{"out"}}
};

std::vector<NodeDef> defsForListBox{NodeWithInput, NodeWithOutput};

GraphEditorWindow::GraphEditorWindow() {
  ImNodes::CreateContext();
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
      // context menu for creating nodes
      if(ImGui::BeginPopupContextWindow()) {
        int currentItem = -1;
        const char* names[] = {defsForListBox[0].name.c_str(), defsForListBox[1].name.c_str()};
        if (ImGui::ListBox("##label", &currentItem, names, (int)defsForListBox.size(), 4)) {
          NodeInfo n;
          n.name = defsForListBox[currentItem].name;
          _nodeIds.get(n.id);
          for (const auto& p : defsForListBox[currentItem].inputPorts) {
            PortInfo pi;
            pi.name = p.name;
            _portIds.get(pi.id);
            n.inputPorts.emplace_back(std::move(pi));
          }
          for (const auto& p : defsForListBox[currentItem].outputPorts) {
            PortInfo pi;
            pi.name = p.name;
            _portIds.get(pi.id);
            n.outputPorts.emplace_back(std::move(pi));
          }
          _nodes.emplace_back(std::move(n));
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }

      for (const auto& node: _nodes) {
        NodeGUI::draw(node);
      }
      for (const auto& connection: _connections) {
        ImNodes::Link(connection.id, connection.sourcePortId, connection.destPortId);
      }

      ImNodes::MiniMap();
    }
    ImNodes::EndNodeEditor();

    // make a connection if applicable
    {
      Connection connection;
      if (ImNodes::IsLinkCreated(&connection.sourceNodeId,
                                 &connection.sourcePortId,
                                 &connection.destNodeId,
                                 &connection.destPortId)) {
        _connectionIds.get(connection.id);
        _connections.emplace_back(connection);
      }
    }
  }
  ImGui::End();

  return Status::Ok;
}
