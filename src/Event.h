#pragma once
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

// tbf idk what happened. Lets engineer. 

class EventListener;

template <typename... Args>
class EventFunctionWrapper
{
public:
    EventListener* object;
    void (EventListener::*member_function)(Args...);

    void call(Args&&... args)
    {
        (object->*member_function)(std::forward<Args>(args)...);
    }

    bool operator==(const EventFunctionWrapper& other) const
    {
        return object == other.object && member_function == other.member_function;
    }
};

class BaseEvent
{
public:
    BaseEvent() = default;
    virtual ~BaseEvent() = default;

protected:
    friend EventListener;
    virtual void remove_all_listener_of_class(EventListener* listener) = 0;
};

template <typename... Args>
class Event final : public BaseEvent
{
public:
    Event() = default;
    ~Event() override;

    Event(const Event& other) = delete;
    Event(Event&& other) = delete;
    Event& operator=(const Event& other) = delete;
    Event& operator=(Event&& other) = delete;

    template <typename EventListenerObject> requires std::derived_from<EventListenerObject, EventListener>
    void add_listener(EventListenerObject* listener, void (EventListenerObject::*member_function)(Args...));

    template <typename EventListenerObject> requires std::derived_from<EventListenerObject, EventListener>
    void remove_listener(EventListenerObject* listener, void (EventListenerObject::*member_function)(Args...));


    void notify_listeners(Args... args);

protected:
    void remove_all_listener_of_class(EventListener* listener) override;

private:
    std::vector<EventFunctionWrapper<Args...>> m_function_pointers;
    bool m_is_notifying = false;
};

#include "EventListener.h"

template <typename... Args>
Event<Args...>::~Event()
{
    for (EventFunctionWrapper<Args...>& function : m_function_pointers)
    {
        function.object->remove_from_event_internal(this);
    }
}

template <typename... Args>
template <typename EventListenerObject> requires std::derived_from<EventListenerObject, EventListener>
void Event<Args...>::add_listener(EventListenerObject* listener, void (EventListenerObject::*member_function)(Args...))
{
    EventListener* lister = static_cast<EventListener*>(listener);
    void (EventListener::*caller)(Args...) = static_cast<void (EventListener::*)(Args...)>(member_function);
    listener->add_to_event_internal(this);
    m_function_pointers.emplace_back(lister, caller);
}

template <typename... Args>
template <typename EventListenerObject> requires std::derived_from<EventListenerObject, EventListener>
void Event<Args...>::remove_listener(EventListenerObject* listener, void (EventListenerObject::*member_function)(Args...))
{
    assert(!m_is_notifying && "Dont delete events while notifying");

    EventListener* lister = static_cast<EventListener*>(listener);
    void (EventListener::*caller)(Args...) = static_cast<void (EventListener::*)(Args...)>(member_function);

    EventFunctionWrapper<Args...> event_wrapper(lister, caller);
    std::erase(m_function_pointers, event_wrapper);
}

template <typename... Args>
void Event<Args...>::remove_all_listener_of_class(EventListener* listener)
{
    std::erase_if(m_function_pointers, [&](EventFunctionWrapper<Args...> function)
    {
        return function.object == listener;
    });
}

template <typename... Args>
void Event<Args...>::notify_listeners(Args... args)
{
    m_is_notifying = true;
    for (EventFunctionWrapper<Args...> function : m_function_pointers)
    {
        function.call(std::forward<Args>(args)...);
    }
    m_is_notifying = false;
}
