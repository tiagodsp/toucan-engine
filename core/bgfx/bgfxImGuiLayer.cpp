#include "bgfxImGuiLayer.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/WindowEvents.h"
#include "CoreTypes.h"
#include "Events.h"
#include "Globals.h"
#include "Log.h"
#include "Toucan.h"

#include "bgfx/bgfx.h"
#include "imgui.h"
#include "imgui_impl_bgfx.h"

namespace Toucan
{

BgfxImGuiLayer::BgfxImGuiLayer()
{
}

BgfxImGuiLayer::~BgfxImGuiLayer() {}

void BgfxImGuiLayer::OnAttach() 
{
    m_ImGuiContext = ImGui::CreateContext();
    ImGui_Implbgfx_Init(0);
    ImGui::GetIO().DisplaySize = {(float)Global::g_Window->GetWindowSize().x, (float)Global::g_Window->GetWindowSize().y};
    ImGui::GetIO().BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    ImGui::GetIO().BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    // ImGui::GetIO().ConfigFlags  |= ImGuiConfigFlags_NavEnableKeyboard;
    // ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void BgfxImGuiLayer::OnDetach()
{
    ImGui_Implbgfx_Shutdown();
    ImGui::DestroyContext();
}

void BgfxImGuiLayer::Begin()
{
    ImGui_Implbgfx_NewFrame();
    ImGui::NewFrame();
}

void BgfxImGuiLayer::End() 
{
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)Global::g_Window->GetWindowSize().x, (float)Global::g_Window->GetWindowSize().y);

    ImGui::Render();
    ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
}

void BgfxImGuiLayer::OnUpdate()
{
}

void BgfxImGuiLayer::OnImGuiRender(ImGuiContext *context)
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void BgfxImGuiLayer::OnEvent(Event *event)
{
    EventForwarder forwarder(event);
    forwarder.Dispatch<WindowResizeEvent>([this](const Event *event) {
        const WindowResizeEvent *e = static_cast<const WindowResizeEvent *>(event);
        ImGui::GetIO().DisplaySize = {(float)e->GetWidth(), (float)e->GetHeight()};
        ImGui::GetIO().DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        return true;
    });
    forwarder.Dispatch<MouseMotionEvent>([this](const Event *event) {
        const MouseMotionEvent *e = static_cast<const MouseMotionEvent *>(event);
        const Vector2Int MousePos = e->GetPosition();
        ImGui::GetIO().MousePos = {(float)MousePos.x, (float)MousePos.y};
        return true;
    });
    forwarder.Dispatch<MouseKeyPressedEvent>([this](const Event *event) {
        const MouseKeyPressedEvent *e = static_cast<const MouseKeyPressedEvent *>(event);
        CORE_LOGW("MouseKeyPressedEvent: {}", e->GetKeyCode());
        ImGuiIO &io = ImGui::GetIO();
        switch (e->GetKeyCode())
        {
            case 1:
                io.MouseDown[0] = true;
                break;
            case 2:
                io.MouseDown[2] = true;
                break;
            case 3:
                io.MouseDown[1] = true;
                break;
            default:
                break;
        }
        return true;
    });
    forwarder.Dispatch<MouseKeyReleasedEvent>([this](const Event *event) {
        const MouseKeyReleasedEvent *e = static_cast<const MouseKeyReleasedEvent *>(event);
        CORE_LOGW("MouseKeyReleasedEvent: {}", e->GetKeyCode());
        ImGuiIO &io = ImGui::GetIO();
        switch (e->GetKeyCode())
        {
            case 1:
                io.MouseDown[0] = false;
                break;
            case 2:
                io.MouseDown[2] = false;
                break;
            case 3:
                io.MouseDown[1] = false;
                break;
            default:
                break;
        }
        return true;
    });
}

} // namespace Toucan