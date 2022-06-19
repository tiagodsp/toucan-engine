#pragma once
#include "CoreTypes.h"
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
  public:
    virtual void Update() = 0;
    static Ref<Window> Create(WindowInitializationParams params);
    inline HANDLE GetNativeWindow() const { return m_NativeWindowHandle; }

  protected:
    HANDLE m_NativeWindowHandle;
};

} // namespace Toucan