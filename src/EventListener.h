#pragma once
#include <unordered_set>

class BaseEvent;
template <typename... Args>
class Event;


class EventListener
{
public:
    EventListener() = default;
    virtual ~EventListener();

    EventListener(const EventListener& other) = delete;
    EventListener(EventListener&& other) = delete;
    EventListener& operator=(const EventListener& other) = delete;
    EventListener& operator=(EventListener&& other) = delete;

private:
    template <typename... Args>
    friend class Event;

    void add_to_event_internal(BaseEvent* event);
    void remove_from_event_internal(BaseEvent* event);

    std::unordered_set<BaseEvent*> m_event;
};

#include "Event.h"

inline EventListener::~EventListener()
{
    for (BaseEvent* event : m_event)
    {
        event->remove_all_listener_of_class(this);
    }
}

inline void EventListener::add_to_event_internal(BaseEvent* event)
{
    m_event.emplace(event);
}

inline void EventListener::remove_from_event_internal(BaseEvent* event)
{
    m_event.erase(event);
}


// template <typename... Args>
// EventListener<Args...>::~EventListener()
// {
//     if (m_event != nullptr)
//     {
//         m_event->remove_listener(this);
//     }
// }
//
// template <typename... Args>
// void EventListener<Args...>::add_to_event_internal(Event<Args...>* event)
// {
//     m_event = event;
// }
//
// template <typename... Args>
// void EventListener<Args...>::remove_from_event_internal()
// {
//     m_event = nullptr;
// }

