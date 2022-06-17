#pragma once
#include "Log.h"
#include "Toucan.h"
#include <cstddef>
#include <cstdlib>
#include <type_traits>

namespace Toucan
{
class Event
{
  public:
    Event(){};
    ~Event(){};
    REFLECTION_BEGIN(Event)
    REFLECTION_END()
};

class EventDispatcher
{
    static EventDispatcher m_Instance;

  public:
    using EventHandler = std::function<void(const Event *)>;

  private:
    using HandlerList = std::vector<EventHandler>;
    std::map<String, HandlerList> m_HandlerMap;

    template <typename T> static char TestIsEventType(Event);
    template <typename T> static int TestIsEventType(...);
    template <typename T> struct IsEventType
    {
        static constexpr bool value = sizeof(TestIsEventType<T>()) == sizeof(char);
    };

  public:
    static EventDispatcher &Get() { return m_Instance; }

    void Dispatch(const Event *e)
    {
        auto handlers = m_HandlerMap.find(e->GetDerivedType().Name);
        if (handlers != m_HandlerMap.end())
        {
            for (auto h : handlers->second) { h(e); }
        }
    }

    template <typename E, typename std::enable_if<!TypeRegister::IsReflected<E>::value, int>::type = 0>
    void AddEventLister(EventHandler Handler);

    template <typename E, typename std::enable_if<TypeRegister::IsReflected<E>::value, int>::type = 0>
    void AddEventListener(EventHandler Handler)
    {
        auto baseType = E::StaticType.BaseClass;
        while (baseType != nullptr)
        {
            if (baseType == &Event::StaticType)
            {
                m_HandlerMap[E::StaticType.Name].push_back(Handler);
                return;
            }
            baseType = baseType->BaseClass;
        }
        CORE_LOGF("Failed to add event listener for type {}. Not derived from Toucan::Event.", E::StaticType.Name);
    }
};
} // namespace Toucan