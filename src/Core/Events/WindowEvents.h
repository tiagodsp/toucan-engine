#pragma once
#include "Toucan.h"

namespace Toucan
{
class WindowCloseEvent : public Event
{
    REFLECTION_BEGIN(WindowCloseEvent)
    REFLECTION_END();
};

} // namespace Toucan