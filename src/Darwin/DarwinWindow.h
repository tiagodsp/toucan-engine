#pragma once
#include "Toucan.h"

namespace Toucan
{
class DarwinWindow : public Window
{
  public:
    DarwinWindow(WindowInitializationParams params);
    virtual void Update() override;

  private:
    HANDLE m_SDLWindowHandle;
    HANDLE m_SDLRendererHandle;
};
} // namespace Toucan