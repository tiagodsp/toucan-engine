#pragma once
#include "Toucan.h"

namespace Toucan
{

struct WindowInitializationParams
{
    std::string Title;
    glm::vec<2, int> Resolution;
    glm::vec<2, int> InitialPosition{0, 0};
};

class Window
{
  protected:
    Window(WindowInitializationParams params);

  public:
    void Update();
    static Ref<Window> Create(WindowInitializationParams params);

  private:
    HANDLE m_WindowHandle;
    HANDLE m_RendererHandle;
};

} // namespace Toucan