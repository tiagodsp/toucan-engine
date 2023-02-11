#pragma once
#include "Log.h"
#include "Toucan.h"
#include <cstddef>
#include <cstdlib>
#include <type_traits>

namespace Toucan
{

/**
 * @class Event
 * @brief Base class for all events.
 */
class Event
{
    friend class EventForwarder;
    bool m_IsHandled = false;

  public:
    Event(){};
    ~Event(){};
    const bool IsHandled() const { return m_IsHandled; }
    REFLECTION_BEGIN(Event)
    REFLECTION_END()
};

/**
 * @class EventNotifier
 * @brief A singleton class that manages event listeners and broadcasts events to them.
 */
class EventNotifier
{
    static EventNotifier m_Instance;

  public:
    using EventHandler = std::function<void(const Event *)>;

  private:
    using HandlerList = std::vector<EventHandler>;
    std::map<String, HandlerList> m_HandlerMap;

  public:
    static EventNotifier &Get() { return m_Instance; }

    void Broadcast(const Event *e)
    {
        auto handlers = m_HandlerMap.find(e->GetDerivedType().Name);
        if (handlers != m_HandlerMap.end())
        {
            for (auto h : handlers->second)
            {
                h(e);
            }
        }
    }

    template <typename E, typename std::enable_if<!TypeRegister::IsReflected<E>::value, int>::type = 0>
    void AddEventListener(EventHandler Handler);

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

/**
 * @class EventForwarder
 * @brief A helper class that forwards events to a handler function.
 */
class EventForwarder
{
    Event *m_Event;

  public:
    /**
     * @brief Handler function type. Should return true if the event was handled.
     */
    using EventHandler = std::function<bool(Event *)>;

  public:
    EventForwarder(Event *e) : m_Event(e) {}

    template <typename E, typename std::enable_if<TypeRegister::IsReflected<E>::value, int>::type = 0>
    bool Dispatch(EventHandler Handler)
    {
        if (E::StaticType.Name == m_Event->GetDerivedType().Name)
        {
            m_Event->m_IsHandled = Handler(m_Event);
            return m_Event->m_IsHandled;
        }
        return false;
    }
};
} // namespace Toucan