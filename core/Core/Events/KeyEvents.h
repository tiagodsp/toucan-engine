#pragma once
#include "Events.h"

namespace Toucan
{

class CORE_API KeyEvent : public Event
{
    int m_KeyCode;

  public:
    KeyEvent() : m_KeyCode(-1) {}
    KeyEvent(int keyCode) : m_KeyCode(keyCode) {}
    inline int GetKeyCode() const { return m_KeyCode; }

    REFLECTION_BEGIN(KeyEvent)
    REFLECTION_MEMBER(int, m_KeyCode)
    REFLECTION_END()
};

class CORE_API KeyPressedEvent : public KeyEvent
{
  public:
    KeyPressedEvent() : KeyEvent(-1) {}
    KeyPressedEvent(int keyCode) : KeyEvent(keyCode) {}

    REFLECTION_BEGIN(KeyPressedEvent)
    REFLECTION_END()
};

class CORE_API KeyReleasedEvent : public KeyEvent
{
  public:
    KeyReleasedEvent() : KeyEvent(-1) {}
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

    REFLECTION_BEGIN(KeyReleasedEvent)
    REFLECTION_END()
};

} // namespace Toucan