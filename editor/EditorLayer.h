#pragma once
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
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

  private:
    Ref<Renderer> m_Renderer;
    Ref<Renderer2D> m_Renderer2D;
};
} // namespace Toucan