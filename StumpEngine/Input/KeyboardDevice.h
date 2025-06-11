#pragma once

#include "InputBinding.h"

#include <span>
#include <vector>
#include <SDL3/SDL_keycode.h>

namespace stump
{
    struct ButtonBindingKeyboard
    {
        SDL_Scancode        key;
        bool                pressed_last_frame;
        InputBindingButton* binding;
    };

    struct AxisBindingKeyboard
    {
        SDL_Scancode      axis;
        bool              pressed_last_frame;
        InputBindingAxis* binding;
    };

    struct VectorBindingKeyboard
    {
        SDL_Scancode        y_up;
        SDL_Scancode        y_down;
        SDL_Scancode        x_left;
        SDL_Scancode        x_right;
        glm::vec2           vector_last_frame;
        InputBindingVector* binding;
    };

    class KeyboardDevice final
    {
    public:
        explicit KeyboardDevice();
        void process_device();
        void add_button_binding(InputBindingButton& binding, SDL_Scancode key);
        void remove_button_binding(InputBindingButton& binding);
        void add_axis_binding(InputBindingAxis& binding, SDL_Scancode key);
        void remove_axis_binding(InputBindingAxis& binding);
        void add_vector_binding(InputBindingVector& binding, SDL_Scancode y_up, SDL_Scancode y_down, SDL_Scancode x_left, SDL_Scancode x_right);
        void remove_vector_binding(InputBindingVector& binding);

    private:
        std::span<const bool>              m_sdl_keyboard{};
        std::vector<ButtonBindingKeyboard> m_inputs_button;
        std::vector<AxisBindingKeyboard>   m_inputs_axis;
        std::vector<VectorBindingKeyboard> m_inputs_vector;
    };
} // namespace stump
