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

class Event;

class Window
{
    using EventCallbackFn = std::function<void(Event *)>;

  protected:
    EventCallbackFn m_EventCallback;

  public:
    virtual void Update() = 0;
    void SetEventCallback(const EventCallbackFn &callback) { m_EventCallback = callback; }
    static Ref<Window> Create(WindowInitializationParams params);
    inline HANDLE GetNativeWindow() const { return m_NativeWindowHandle; }

  protected:
    HANDLE m_NativeWindowHandle;
};

} // namespace Toucan