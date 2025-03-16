#pragma once
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

// tbf idk what happened. Lets engineer. 

class BaseEventListener;
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
    std::vector<EventListener<Args...>*> m_function_pointers;
    bool m_is_notifying = false;
};


#include "EventListener.h"

template <typename... Args>
Event<Args...>::~Event()
{
    for (EventListener<Args...>* functions : m_function_pointers)
    {
        functions->remove_from_event_internal();
    }
}

template <typename... Args>
void Event<Args...>::add_listener(EventListener<Args...>* listener)
{
    listener->add_to_event_internal(this);
    m_function_pointers.push_back(listener);
}

template <typename... Args>
void Event<Args...>::remove_listener(EventListener<Args...>* listener)
{
    std::erase(m_function_pointers, listener);
}

template <typename... Args>
void Event<Args...>::notify_listeners(Args... args)
{
    for (EventListener<Args...>* function : m_function_pointers)
    {
        function->call_function(std::forward<Args>(args)...);
    }
}

// Past attempt. But issues came up when needing to cast that had inheriting 2 things. Which was not possible. 

// template <typename... Args>
// Event<Args...>::~Event()
// {
//     for (EventFunctionWrapper<Args...>& function : m_function_pointers)
//     {
//         function.object->remove_from_event_internal(this);
//     }
// }
//
// template <typename... Args>
// template <typename EventListenerObject> requires std::derived_from<EventListenerObject, EventListener>
// void Event<Args...>::add_listener(EventListenerObject* listener, void (EventListenerObject::*member_function)(Args...))
// {
//     EventListener* lister = static_cast<EventListener*>(listener);
//     void (EventListener::*caller)(Args...) = static_cast<void (EventListener::*)(Args...)>(member_function);
//     listener->add_to_event_internal(this);
//     m_function_pointers.emplace_back(lister, caller);
// }
//
// template <typename... Args>
// template <typename EventListenerObject> requires std::derived_from<EventListenerObject, EventListener>
// void Event<Args...>::remove_listener(EventListenerObject* listener, void (EventListenerObject::*member_function)(Args...))
// {
//     assert(!m_is_notifying && "Dont delete events while notifying");
//
//     EventListener* lister = static_cast<EventListener*>(listener);
//     void (EventListener::*caller)(Args...) = static_cast<void (EventListener::*)(Args...)>(member_function);
//     EventFunctionWrapper<Args...> event_wrapper(lister, caller);
//     std::erase(m_function_pointers, event_wrapper);
// }
//
// template <typename... Args>
// void Event<Args...>::remove_all_listener_of_class(EventListener* listener)
// {
//     std::erase_if(m_function_pointers, [&](EventFunctionWrapper<Args...> function)
//     {
//         return function.object == listener;
//     });
// }
//
// template <typename... Args>
// void Event<Args...>::notify_listeners(Args... args)
// {
//     m_is_notifying = true;
//     for (EventFunctionWrapper<Args...> function : m_function_pointers)
//     {
//         function.call(std::forward<Args>(args)...);
//     }
//     m_is_notifying = false;
// }
