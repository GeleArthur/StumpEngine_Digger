#include "InputBinding.h"

namespace stump
{

    bool InputBindingButton::get_current_state() const
    {
        return m_current_data;
    }
    Event<>* InputBindingButton::get_on_pressed()
    {
        return &m_on_pressed;
    }
    Event<>* InputBindingButton::get_on_held_down()
    {
        return &m_on_held_down;
    }
    Event<>* InputBindingButton::get_on_release()
    {
        return &m_on_release;
    }
    void InputBindingButton::update_binding(bool is_pressed_this_frame, bool is_held_down, bool is_released)
    {
        m_current_data = is_held_down;
        if (is_held_down)
        {
            m_on_held_down.notify_listeners();
        }
        if (is_pressed_this_frame)
        {
            m_on_pressed.notify_listeners();
        }
        if (is_released)
        {
            m_on_release.notify_listeners();
        }
    }
    float InputBindingAxis::get_current_state() const
    {
        return m_current_data;
    }
    void InputBindingAxis::update_binding(float axis, bool full_pressed_frame, bool full_release_frame)
    {
        if (m_current_data != axis)
        {
            on_change.notify_listeners(axis);
            m_current_data = axis;
        }

        if (full_pressed_frame)
        {
            on_full_press.notify_listeners(m_current_data);
        }

        if (full_release_frame)
        {
            on_full_release.notify_listeners(m_current_data);
        }
    }
    void InputBindingVector::update_binding(glm::vec2 new_direction)
    {
        if (m_current_data != new_direction)
        {
            m_current_data = new_direction;
            on_change.notify_listeners(m_current_data);
        }
    }
    glm::vec2 InputBindingVector::get_current_state() const
    {
        return m_current_data;
    }
} // namespace stump
