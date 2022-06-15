#pragma once
#include "Toucan.h"

namespace Toucan
{

class Window;

class App
{
  public:
    App(const char *Name);
    void Run();

  private:
    Ref<Window> m_Window;
};

} // namespace Toucan