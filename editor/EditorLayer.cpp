#include "EditorLayer.h"
#include "Core/Events/WindowEvents.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Events.h"
#include <imgui.h>

namespace Toucan
{
EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    m_Renderer = Renderer::Get();
    m_Renderer2D = Renderer2D::Get();
}

EditorLayer::~EditorLayer() {}

void EditorLayer::OnAttach() {}

void EditorLayer::OnDetach() {}

void EditorLayer::OnUpdate()
{
    m_Renderer->Clear({0.1f, 0.1f, 0.1f, 1.0f});
    m_Renderer->Begin();
    m_Renderer2D->DrawRect({0.0f, 0.0f, 100.0f, 100.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    m_Renderer->End();
}

void EditorLayer::OnImGuiRender(ImGuiContext *context)
{
    ImGui::SetCurrentContext(context);

    static bool showAbout = false;

    ImGui::PushID("EditorLayer");
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
    flags |= ImGuiWindowFlags_NoDocking;
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
             ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", 0, flags);
    ImGui::PopStyleVar();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Exit", "Ctrl+Q")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("About Toucan"))
            {
                showAbout = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    if(showAbout)
    {
        ImGui::OpenPopup("AboutToucan");
    }
    if (ImGui::BeginPopupModal("AboutToucan", &showAbout, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Toucan Engine");
        ImGui::Separator();
        ImGui::Text("Version 0.0.1");
        ImGui::Text("Developed by: ");
        ImGui::Text("  - Tiago Patrocínio");
        ImGui::EndPopup();
    }

    ImGuiIO &io = ImGui::GetIO();
    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");

    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::Begin("Properties");
    ImGui::End();

    ImGui::Begin("Log");
    ImGui::End();

    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::PopID();
}

void EditorLayer::OnEvent(Event *event)
{
    EventForwarder forwarder(event);
    forwarder.Dispatch<WindowResizeEvent>([this](const Event *event) {
        const WindowResizeEvent *e = dynamic_cast<const WindowResizeEvent *>(event);
        m_Renderer->SetViewportSize({e->GetWidth(), e->GetHeight()});
        return false;
    });
}

} // namespace Toucan