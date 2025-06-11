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

        for (AxisBindingGamepad& button : m_inputs_axis)
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

        for (auto& [axis_horizontal, axis_vertical, axis_last_frame, binding] : m_inputs_vector)
        {
            const Sint16 new_axis_x = SDL_GetGamepadAxis(m_gamepad, axis_horizontal);
            const Sint16 new_axis_y = SDL_GetGamepadAxis(m_gamepad, axis_vertical);
            const float  amount_x = static_cast<float>(new_axis_x) / static_cast<float>(std::numeric_limits<int16_t>().max());
            const float  amount_y = static_cast<float>(new_axis_y) / static_cast<float>(std::numeric_limits<int16_t>().max());

            glm::vec2 new_direction = glm::vec2(amount_x, amount_y);
            bool      released{};
            bool      pressed{};

            if (glm::dot(new_direction, new_direction) < 0.1f)
            {
                new_direction.x = 0.0f;
                new_direction.y = 0.0f;
            }

            if (glm::dot(new_direction, new_direction) > 0.1f && glm::dot(axis_last_frame, axis_last_frame) < 0.1f)
            {
                pressed = true;
            }
            if (glm::dot(new_direction, new_direction) < 0.1f && glm::dot(axis_last_frame, axis_last_frame) > 0.1f)
            {
                released = true;
            }

            axis_last_frame = new_direction;

            binding->update_binding(new_direction, released, pressed);
        }

        for (auto& [y_up, y_down, x_left, x_right, vector_last, binding] : m_inputs_vector_sides)
        {
            glm::vec2 out{};
            out.x += -1.0f * SDL_GetGamepadButton(m_gamepad, x_left);
            out.x += 1.0f * SDL_GetGamepadButton(m_gamepad, x_right);
            out.y += -1.0f * SDL_GetGamepadButton(m_gamepad, y_up);
            out.y += 1.0f * SDL_GetGamepadButton(m_gamepad, y_down);

            bool release{};
            bool pressed{};

            if ((out.x == 0.0f && out.y == 0.0f) && (vector_last.x != 0.0f || vector_last.y != 0.0f))
            {
                release = true;
            }

            if ((out.x != 0.0f && out.y != 0.0f) && (vector_last.x == 0.0f || vector_last.y == 0.0f))
            {
                pressed = true;
            }

            vector_last = out;

            binding->update_binding(out, release, pressed);
        }
    }
    void GamepadDevice::add_button_binding(InputBindingButton& bind, SDL_GamepadButton button)
    {
        m_inputs_button.emplace_back(button, false, &bind);
    }
    void GamepadDevice::remove_button_binding(const InputBindingButton& bind)
    {
        m_inputs_button.erase(std::ranges::find_if(m_inputs_button, [&](ButtonBindingGamepad& e) {
            return e.binding == &bind;
        }));
    }
    void GamepadDevice::add_axis_binding(InputBindingAxis& bind, SDL_GamepadAxis axis)
    {
        m_inputs_axis.emplace_back(axis, 0, false, &bind);
    }
    void GamepadDevice::remove_axis_binding(const InputBindingAxis& bind)
    {
        m_inputs_axis.erase(std::ranges::find_if(m_inputs_axis, [&](AxisBindingGamepad& e) {
            return e.binding == &bind;
        }));
    }
    void GamepadDevice::add_vector_binding(InputBindingVector& bind, SDL_GamepadAxis axis_x, SDL_GamepadAxis axis_y)
    {
        m_inputs_vector.emplace_back(axis_x, axis_y, glm::vec2{}, &bind);
    }
    void GamepadDevice::remove_vector_binding(const InputBindingVector& bind)
    {
        m_inputs_vector.erase(std::ranges::find_if(m_inputs_vector, [&](VectorBindingGamepad& e) {
            return e.binding == &bind;
        }));
    }
    void GamepadDevice::add_vector_sides_binding(InputBindingVector& bind, SDL_GamepadButton y_up, SDL_GamepadButton y_down, SDL_GamepadButton x_left, SDL_GamepadButton x_right)
    {
        m_inputs_vector_sides.emplace_back(y_up, y_down, x_left, x_right, glm::vec2{}, &bind);
    }
    void GamepadDevice::remove_vector_sides_binding(const InputBindingVector& bind)
    {
        m_inputs_vector_sides.erase(std::ranges::find_if(m_inputs_vector_sides, [&](VectorSidesBindingGamepad& e) {
            return e.binding == &bind;
        }));
    }
} // namespace stump