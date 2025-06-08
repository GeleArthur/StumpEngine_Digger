#pragma once
#include <functional>
#include <iostream>
#include <vector>

namespace stump
{
    class BaseEventListener;
    template<typename... Args>
    class EventListener;

    template<typename... Args>
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
        bool                                 m_is_notifying = false;
    };

    // #include "EventListener.h"

    template<typename... Args>
    Event<Args...>::~Event()
    {
        for (EventListener<Args...>* functions : m_function_pointers)
        {
            functions->remove_from_event_internal();
        }
    }

    template<typename... Args>
    void Event<Args...>::add_listener(EventListener<Args...>* listener)
    {
        listener->add_to_event_internal(this);
        m_function_pointers.push_back(listener);
    }

    template<typename... Args>
    void Event<Args...>::remove_listener(EventListener<Args...>* listener)
    {
        listener->remove_from_event_internal();
        std::erase(m_function_pointers, listener);
    }

    template<typename... Args>
    void Event<Args...>::notify_listeners(Args... args)
    {
        for (EventListener<Args...>* function : m_function_pointers)
        {
            // std::forward<Args...>(args...);
            function->call_function(std::forward<Args>(args)...);
        }
    }
} // namespace stump
