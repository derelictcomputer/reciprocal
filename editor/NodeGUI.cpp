#include "imnodes.h"
#include "NodeGUI.h"

using namespace dc;


Status NodeGUI::draw(const NodeInfo& info) {
  ImNodes::BeginNode(info.id);
  {
    // title
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(info.name.c_str());
    ImNodes::EndNodeTitleBar();

    // content within node
    ImGui::Dummy(ImVec2(80.0f, 45.0f));

    // inputs
    for (const auto& input : info.inputPorts) {
      ImNodes::BeginInputAttribute(input.id);
      ImGui::TextUnformatted(input.name.c_str());
      ImNodes::EndInputAttribute();
    }

    // outputs
    for (const auto& output : info.outputPorts) {
      ImNodes::BeginOutputAttribute(output.id);
      ImGui::TextUnformatted(output.name.c_str());
      ImNodes::EndOutputAttribute();
    }
  }
  ImNodes::EndNode();

  return Status::Ok;
}
