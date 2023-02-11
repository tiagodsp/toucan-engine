#pragma once
#include "Toucan.h"

namespace Toucan
{
class WindowCloseEvent : public Event
{
    REFLECTION_BEGIN(WindowCloseEvent)
    REFLECTION_END();
};

class WindowResizeEvent : public Event
{
  private:
    uint32 m_Width;
    uint32 m_Height;

  public:
    WindowResizeEvent() : m_Width(0), m_Height(0) {}
    WindowResizeEvent(uint32 width, uint32 height) : m_Width(width), m_Height(height) {}
    const uint32 GetWidth() const { return m_Width; }
    const uint32 GetHeight() const { return m_Height; }

    REFLECTION_BEGIN(WindowResizeEvent)
    REFLECTION_END();
};

} // namespace Toucan