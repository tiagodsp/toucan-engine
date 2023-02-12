#pragma once
#include "Toucan.h"
#include "glm/fwd.hpp"

namespace Toucan
{
class CORE_API MouseEvent : public Event
{
    Vector2Int m_Position;

  public:
    MouseEvent() : m_Position(0, 0) {}
    MouseEvent(Vector2Int position) : m_Position(position) {}
    inline Vector2Int GetPosition() const { return m_Position; }

    REFLECTION_BEGIN(MouseEvent)
    REFLECTION_MEMBER(Vector2Int, m_Position)
    REFLECTION_END()
};

class CORE_API MouseKeyEvent : public MouseEvent
{
    int m_KeyCode;

  public:
    MouseKeyEvent() : MouseEvent({0, 0}), m_KeyCode(-1) {}
    MouseKeyEvent(Vector2Int position, int keyCode) : MouseEvent(position), m_KeyCode(keyCode) {}
    inline int GetKeyCode() const { return m_KeyCode; }

    REFLECTION_BEGIN(MouseKeyEvent)
    REFLECTION_MEMBER(int, m_KeyCode)
    REFLECTION_END()
};

class CORE_API MouseKeyPressedEvent : public MouseKeyEvent
{
  public:
    MouseKeyPressedEvent() : MouseKeyEvent({0, 0}, -1) {}
    MouseKeyPressedEvent(Vector2Int position, int keyCode) : MouseKeyEvent(position, keyCode) {}

    REFLECTION_BEGIN(MouseKeyPressedEvent)
    REFLECTION_END()
};

class CORE_API MouseKeyReleasedEvent : public MouseKeyEvent
{
  public:
    MouseKeyReleasedEvent() : MouseKeyEvent({0, 0}, -1) {}
    MouseKeyReleasedEvent(Vector2Int position, int keyCode) : MouseKeyEvent(position, keyCode) {}

    REFLECTION_BEGIN(MouseKeyReleasedEvent)
    REFLECTION_END()
};

class CORE_API MouseMotionEvent : public MouseEvent
{
    Vector2Int m_Delta;

  public:
    MouseMotionEvent() : MouseEvent({0, 0}), m_Delta({0, 0}) {}
    MouseMotionEvent(Vector2Int position, Vector2Int delta) : MouseEvent(position), m_Delta(delta) {}
    inline Vector2Int GetDelta() const { return m_Delta; }

    REFLECTION_BEGIN(MouseMotionEvent)
    REFLECTION_MEMBER(Vector2Int, m_Delta)
    REFLECTION_END()
};
} // namespace Toucan