#pragma once
#include "Core/Window.h"

union SDL_Event;

namespace Toucan
{
class CORE_LOCAL DarwinWindow : public Window
{
  public:
    DarwinWindow(WindowInitializationParams params);
    virtual void Update() override;

  private:
    void PollEvents();

  private:
    HANDLE m_SDLWindowHandle;
    HANDLE m_SDLRendererHandle;
};
} // namespace Toucan