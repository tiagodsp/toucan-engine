#include "Events.h"

REFLECTION_INIT(Toucan::Event);
namespace Toucan
{

EventDispatcher EventDispatcher::m_Instance;

template <typename E, typename std::enable_if<!TypeRegister::IsReflected<E>::value, int>::type>
void AddEventLister(EventDispatcher::EventHandler Handler)
{
    LOGF(Events, "Event type does not derive from Toucan::Event class.");
    exit(1);
}
} // namespace Toucan