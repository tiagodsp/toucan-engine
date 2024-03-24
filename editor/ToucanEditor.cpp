#include "ToucanEditor.h"
#include "App.h"
#include "EditorLayer.h"
#include "ImGui/ImGuiLayer.h"

namespace Toucan {

ToucanEditor::ToucanEditor()
    : App("Toucan Editor")
{
    Ref<EditorLayer> editorLayer = std::make_shared<EditorLayer>();
    PushLayer(editorLayer);
}

ToucanEditor::~ToucanEditor()
{
}

} // namespace Toucan

int main()
{
    Toucan::ToucanEditor editor;
    editor.Run();
    return 0;
}