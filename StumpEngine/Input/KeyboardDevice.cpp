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
}
void stump::KeyboardDevice::add_button_binding(InputBindingButton& binding, SDL_Keycode key)
{
    m_inputs_button.emplace_back(key, false, &binding);
}
void stump::KeyboardDevice::add_axis_binding(InputBindingAxis& binding, SDL_Keycode key)
{
}
void stump::KeyboardDevice::add_vector_binding(InputBindingAxis& binding, SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right)
{
}