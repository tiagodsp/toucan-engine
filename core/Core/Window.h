#pragma once
#include "CoreTypes.h"

namespace Toucan
{

struct WindowInitializationParams
{
    std::string Title;
    glm::vec<2, int> Resolution;
    glm::vec<2, int> InitialPosition{0, 0};
};

class Event;

class CORE_API Window
{
    using EventCallbackFn = std::function<void(Event *)>;

  protected:
    EventCallbackFn m_EventCallback;

  public:
    virtual void Update() = 0;
    void SetEventCallback(const EventCallbackFn &callback) { m_EventCallback = callback; }
    static Ref<Window> Create(WindowInitializationParams params);
    inline HANDLE GetNativeWindow() const { return m_NativeWindowHandle; }

    Vector2Int GetWindowSize() const { return m_WindowSize; }

  protected:
    HANDLE m_NativeWindowHandle;
    Vector2Int m_WindowSize;
};

} // namespace Toucan