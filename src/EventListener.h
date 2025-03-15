#pragma once

template <typename... Args>
class Event;

template <typename... Args>
class EventListener
{
public:
    EventListener() = default;
    virtual ~EventListener();

    EventListener(const EventListener& other) = delete;
    EventListener(EventListener&& other) = delete;
    EventListener& operator=(const EventListener& other) = delete;
    EventListener& operator=(EventListener&& other) = delete;

    virtual void notify(Args... args) = 0;

private:
    friend Event<Args...>;

    void add_to_event_internal(Event<Args...>* event);
    void remove_from_event_internal();

    Event<Args...>* m_event{};
};

template <typename... Args>
EventListener<Args...>::~EventListener()
{
    if (m_event != nullptr)
    {
        m_event->remove_listener(this);
    }
}

template <typename... Args>
void EventListener<Args...>::add_to_event_internal(Event<Args...>* event)
{
    m_event = event;
}

template <typename... Args>
void EventListener<Args...>::remove_from_event_internal()
{
    m_event = nullptr;
}

