#pragma once
#include <unordered_set>

class BaseEvent;

template <typename... Args>
class Event;

template <typename... Args>
class EventListener final
{
public:
    explicit EventListener(std::function<void(Args...)> function);
    ~EventListener();

    EventListener(const EventListener& other) = delete;
    EventListener(EventListener&& other) = delete;
    EventListener& operator=(const EventListener& other) = delete;
    EventListener& operator=(EventListener&& other) = delete;

    void call_function(Args&&... args);

private:
    template <typename... Args2>
    friend class Event;

    void add_to_event_internal(Event<Args...>* event);
    void remove_from_event_internal();

    std::function<void(Args...)> m_function;
    Event<Args...>* m_event{};
};

#include "Event.h"

template <typename... Args>
EventListener<Args...>::EventListener(std::function<void(Args...)> function):
    m_function{function}
{
}

template <typename... Args>
EventListener<Args...>::~EventListener()
{
    if (m_event != nullptr)
    {
        m_event->remove_listener(this);
    }
}

template <typename... Args>
void EventListener<Args...>::call_function(Args&&... args)
{
    m_function(std::forward<Args>(args)...);
}

template <typename... Args>
void EventListener<Args...>::add_to_event_internal(Event<Args...>* event)
{
    assert(m_event == nullptr && "Please remove event before assigning a new one");
    m_event = event;
}

template <typename... Args>
void EventListener<Args...>::remove_from_event_internal()
{
    m_event = nullptr;
}

