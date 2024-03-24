#pragma once
#include "ImGui/ImGuiLayer.h"
#include <imgui.h>

namespace Toucan
{
class CORE_LOCAL BgfxImGuiLayer : public ImGuiLayer
{
  public:
    BgfxImGuiLayer();
    virtual ~BgfxImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void Begin() override;
    virtual void End() override;
    virtual void OnImGuiRender(ImGuiContext* context) override;
    virtual ImGuiContext* GetImGuiContext() override { return m_ImGuiContext; }
    virtual void OnEvent(Event *event) override;
  
  private:
    ImGuiContext* m_ImGuiContext;
};
} // namespace Toucan