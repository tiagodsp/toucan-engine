#pragma once
#include "Toucan.h"

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
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event *event) override;
};
} // namespace Toucan