#include "imnodes.h"
#include "GraphEditorWindow.h"

using namespace dc;

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
      ImNodes::BeginNode(1);
      {
        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Out Node");
        ImNodes::EndNodeTitleBar();
        ImGui::Dummy(ImVec2(80.0f, 45.0f));
        ImNodes::BeginOutputAttribute(3);
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
      }
      ImNodes::EndNode();

      ImNodes::BeginNode(2);
      {
        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("In Node");
        ImNodes::EndNodeTitleBar();
        ImGui::Dummy(ImVec2(80.0f, 45.0f));
        ImNodes::BeginInputAttribute(4);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();
      }
      ImNodes::EndNode();
    }
    ImNodes::EndNodeEditor();
  }
  ImGui::End();

  return Status::Ok;
}
