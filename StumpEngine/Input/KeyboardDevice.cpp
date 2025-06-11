#include "KeyboardDevice.h"
#include <sdl3/SDL.h>

stump::KeyboardDevice::KeyboardDevice()
{
    int count{};
    SDL_GetKeyboardState(&count);

    m_sdl_keyboard = std::span(SDL_GetKeyboardState(nullptr), count);
}
void stump::KeyboardDevice::process_device()
{
    for (auto& [key, pressed_last_frame, binding] : m_inputs_button)
    {
        bool       held_down = m_sdl_keyboard[key];
        const bool pressed_this_frame = held_down == true && pressed_last_frame == false;
        const bool released_this_frame = held_down == false && pressed_last_frame == true;

        pressed_last_frame = held_down;

        binding->update_binding(pressed_this_frame, held_down, released_this_frame);
    }

    for (auto& [key, pressed_last_frame, binding] : m_inputs_axis)
    {
        bool       held_down = m_sdl_keyboard[key];
        const bool pressed_this_frame = held_down == true && pressed_last_frame == false;
        const bool released_this_frame = held_down == false && pressed_last_frame == true;

        pressed_last_frame = held_down;
        binding->update_binding(held_down ? 0.0f : 1.0f, pressed_this_frame, released_this_frame);
    }

    for (auto [y_up, y_down, x_left, x_right, vector_last, binding] : m_inputs_vector)
    {
        glm::vec2 out{};
        out.x += -1.0f * m_sdl_keyboard[x_left];
        out.x += 1.0f * m_sdl_keyboard[x_right];

        out.y += -1.0f * m_sdl_keyboard[y_up];
        out.y += 1.0f * m_sdl_keyboard[y_down];

        bool release{};
        bool pressed{};

        if ((out.x == 0.0f && out.y == 0.0f) && (vector_last.x != 0.0f && vector_last.y != 0.0f))
        {
            release = true;
        }

        if ((out.x != 0.0f && out.y != 0.0f) && (vector_last.x == 0.0f && vector_last.y == 0.0f))
        {
            pressed = true;
        }

        binding->update_binding(out, release, pressed);
    }
}
void stump::KeyboardDevice::add_button_binding(InputBindingButton& binding, SDL_Scancode key)
{
    m_inputs_button.emplace_back(key, false, &binding);
}
void stump::KeyboardDevice::remove_button_binding(InputBindingButton& binding)
{
    m_inputs_button.erase(std::ranges::find_if(m_inputs_button, [&](const ButtonBindingKeyboard& e) {
        return e.binding == &binding;
    }));
}
void stump::KeyboardDevice::add_axis_binding(InputBindingAxis& binding, SDL_Scancode key)
{
    m_inputs_axis.emplace_back(key, false, &binding);
}
void stump::KeyboardDevice::remove_axis_binding(InputBindingAxis& binding)
{
    m_inputs_axis.erase(std::ranges::find_if(m_inputs_axis, [&](const AxisBindingKeyboard& e) {
        return e.binding == &binding;
    }));
}
void stump::KeyboardDevice::add_vector_binding(InputBindingVector& binding, SDL_Scancode y_up, SDL_Scancode y_down, SDL_Scancode x_left, SDL_Scancode x_right)
{
    m_inputs_vector.emplace_back(y_up, y_down, x_left, x_right, glm::vec2{}, &binding);
}
void stump::KeyboardDevice::remove_vector_binding(InputBindingVector& binding)
{
    m_inputs_vector.erase(std::ranges::find_if(m_inputs_vector, [&](const VectorBindingKeyboard& e) {
        return e.binding == &binding;
    }));
}
