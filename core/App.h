#pragma once
#include "CoreTypes.h"

namespace Toucan
{

class Window;
class Layer;
class LayerStack;
class Event;

class CORE_API App
{
  public:
    App(const char *Name);
    void Run();

    void OnEvent(Event *event);

    void PushLayer(Ref<Layer> layer);
    void PushOverlay(Ref<Layer> overlay);

  private:
    Ref<Window> m_Window;
    Ref<LayerStack> m_LayerStack;
    bool m_ShouldTerminate = false;
};

} // namespace Toucan