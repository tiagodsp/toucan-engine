#pragma once
#include "Toucan.h"

namespace Toucan
{
class EditorLayer : public Layer
{
  public:
    EditorLayer();
    virtual ~EditorLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event *event) override;
};
} // namespace Toucan