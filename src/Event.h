#pragma once
#include <cassert>
#include <iostream>
#include <vector>

template <typename... Args>
class EventListener;

template <typename... Args>
class Event final
{
public:
    Event() = default;
    ~Event();

    Event(const Event& other) = delete;
    Event(Event&& other) = delete;
    Event& operator=(const Event& other) = delete;
    Event& operator=(Event&& other) = delete;

    void add_listener(EventListener<Args...>* listener);
    void remove_listener(EventListener<Args...>* listener);
    void notify_listeners(Args... args);

private:
    std::vector<EventListener<Args...>*> m_events;
    bool m_is_notifying = false;
};

template <typename... Args>
Event<Args...>::~Event()
{
    for (EventListener<Args...>* event : m_events)
    {
        event->remove_from_event_internal();
    }
}

template <typename... Args>
void Event<Args...>::add_listener(EventListener<Args...>* listener)
{
    m_events.push_back(listener);
    listener->add_to_event_internal(this);
}

template <typename... Args>
void Event<Args...>::remove_listener(EventListener<Args...>* listener)
{
    assert(!m_is_notifying && "Dont delete events while notifing");
    std::erase(m_events, listener);
}

template <typename... Args>
void Event<Args...>::notify_listeners(Args... args)
{
    m_is_notifying = true;
    for (auto event : m_events)
    {
        event->notify(std::forward<Args>(args)...);
    }
    m_is_notifying = false;
}
