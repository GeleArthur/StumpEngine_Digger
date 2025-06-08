#pragma once

#include "InputBinding.h"

#include <span>
#include <vector>
#include <SDL3/SDL_keycode.h>

namespace stump
{
    struct ButtonBindingKeyboard
    {
        SDL_Keycode         key;
        bool                pressed_last_frame;
        InputBindingButton* binding;
    };
    //
    // struct AxisBinding
    // {
    //     SDL_GamepadAxis   axis;
    //     Sint16            axis_last_frame;
    //     bool              full_pressed;
    //     InputBindingAxis& binding;
    // };
    //
    // struct VectorBinding
    // {
    //     SDL_GamepadAxis     axis_horizontal;
    //     SDL_GamepadAxis     axis_vertical;
    //     glm::vec2           axis_last_frame;
    //     InputBindingVector& binding;
    // };

    class KeyboardDevice
    {
    public:
        explicit KeyboardDevice();
        void process_device();
        void add_button_binding(InputBindingButton& binding, SDL_Keycode key);
        void add_axis_binding(InputBindingAxis& binding, SDL_Keycode key);
        void add_vector_binding(InputBindingAxis& binding, SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right);

    private:
        std::span<const bool>              m_sdl_keyboard{};
        std::vector<ButtonBindingKeyboard> m_inputs_button;
        // std::vector<AxisBinding>   m_inputs_axis;
        // std::vector<VectorBinding> m_inputs_vector;
        // SDL_Gamepad*               m_gamepad{};
    };
} // namespace stump
