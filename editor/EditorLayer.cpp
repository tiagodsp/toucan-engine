#include "EditorLayer.h"
#include "Core/Events/WindowEvents.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Events.h"

namespace Toucan
{
EditorLayer::EditorLayer() : Layer("EditorLayer") {
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

void EditorLayer::OnImGuiRender() {}

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