#pragma once
#include <Event.h>
#include <EventListener.h>
#include <glm.hpp>

namespace stump
{
    class InputBindingButton final
    {
    public:
        InputBindingButton() = default;
        ~InputBindingButton() = default;

        InputBindingButton(const InputBindingButton& other) = delete;
        InputBindingButton(InputBindingButton&& other) = delete;
        InputBindingButton& operator=(const InputBindingButton& other) = delete;
        InputBindingButton& operator=(InputBindingButton&& other) = delete;

        Event<>* get_on_pressed();
        Event<>* get_on_held_down();
        Event<>* get_on_release();

        void               update_binding(bool is_pressed_this_frame, bool is_held_down, bool is_released);
        [[nodiscard]] bool get_current_state() const;

    private:
        Event<> m_on_pressed;
        Event<> m_on_held_down;
        Event<> m_on_release;
        bool    m_current_data{};
    };

    class InputBindingAxis final
    {
    public:
        InputBindingAxis() = default;
        ~InputBindingAxis() = default;

        InputBindingAxis(const InputBindingAxis& other) = delete;
        InputBindingAxis(InputBindingAxis&& other) = delete;
        InputBindingAxis& operator=(const InputBindingAxis& other) = delete;
        InputBindingAxis& operator=(InputBindingAxis&& other) = delete;

        Event<float> on_full_press;
        Event<float> on_change;
        Event<float> on_full_release;

        void                update_binding(float axis, bool full_pressed_frame, bool full_release_frame);
        [[nodiscard]] float get_current_state() const;

    private:
        bool  m_full_pressed{};
        float m_current_data{};
    };

    class InputBindingVector final
    {
    public:
        explicit InputBindingVector() = default;
        ~InputBindingVector() = default;

        InputBindingVector(const InputBindingVector& other) = delete;
        InputBindingVector(InputBindingVector&& other) = delete;
        InputBindingVector& operator=(const InputBindingVector& other) = delete;
        InputBindingVector& operator=(InputBindingVector&& other) = delete;

        Event<glm::vec2> on_change;

        void                    update_binding(glm::vec2 new_dirction);
        [[nodiscard]] glm::vec2 get_current_state() const;

    private:
        glm::vec2 m_current_data{};
    };
} // namespace stump
