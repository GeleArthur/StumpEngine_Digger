#include "GamepadDevice.h"

namespace stump
{
    GamepadDevice::GamepadDevice(SDL_Gamepad* gamepad)
        : m_gamepad{ gamepad }
    {
    }
    void GamepadDevice::process_device()
    {
        for (auto& [button, pressed_last_frame, binding] : m_inputs_button)
        {
            const bool is_held_down = SDL_GetGamepadButton(m_gamepad, button);
            const bool pressed_this_frame = is_held_down == true && pressed_last_frame == false;
            const bool released_this_frame = is_held_down == false && pressed_last_frame == true;

            pressed_last_frame = is_held_down;

            binding->update_binding(pressed_this_frame, is_held_down, released_this_frame);
        }

        for (AxisBinding& button : m_inputs_axis)
        {
            const Sint16 new_axis = SDL_GetGamepadAxis(m_gamepad, button.axis);
            const float  amount = static_cast<float>(new_axis) / static_cast<float>(std::numeric_limits<int16_t>().max());

            bool full_pressed{};
            bool full_released{};

            if (button.full_pressed == false)
            {
                if (amount > 0.75f)
                {
                    button.full_pressed = true;
                    full_pressed = true;
                }
            }
            else
            {
                if (amount < 0.25f)
                {
                    button.full_pressed = false;
                    full_released = false;
                }
            }

            button.binding->update_binding(amount, full_pressed, full_released);
        }

        for (VectorBinding& vector : m_inputs_vector)
        {
            const Sint16 new_axis_x = SDL_GetGamepadAxis(m_gamepad, vector.axis_horizontal);
            const Sint16 new_axis_y = SDL_GetGamepadAxis(m_gamepad, vector.axis_vertical);
            const float  amount_x = static_cast<float>(new_axis_x) / static_cast<float>(std::numeric_limits<int16_t>().max());
            const float  amount_y = static_cast<float>(new_axis_y) / static_cast<float>(std::numeric_limits<int16_t>().max());

            vector.binding->update_binding(glm::vec2(amount_x, amount_y));
        }
    }
    void GamepadDevice::add_button_binding(SDL_GamepadButton button, InputBindingButton& bind)
    {
        m_inputs_button.emplace_back(button, false, &bind);
    }
    void GamepadDevice::add_axis_binding(SDL_GamepadAxis axis, InputBindingAxis& bind)
    {
        m_inputs_axis.emplace_back(axis, 0, false, &bind);
    }
    void GamepadDevice::add_vector_binding(SDL_GamepadAxis axis_x, SDL_GamepadAxis axis_y, InputBindingVector& bind)
    {
        m_inputs_vector.emplace_back(axis_x, axis_y, glm::vec2{}, &bind);
    }
} // namespace stump