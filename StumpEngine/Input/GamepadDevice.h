#pragma once
#include "InputBinding.h"

#include <unordered_map>
#include <SDL3/SDL_gamepad.h>

namespace stump
{
    struct ButtonBinding
    {
        SDL_GamepadButton   button;
        bool                pressed_last_frame;
        InputBindingButton* binding;
    };

    struct AxisBinding
    {
        SDL_GamepadAxis   axis;
        Sint16            axis_last_frame;
        bool              full_pressed;
        InputBindingAxis* binding;
    };

    struct VectorBinding
    {
        SDL_GamepadAxis     axis_horizontal;
        SDL_GamepadAxis     axis_vertical;
        glm::vec2           axis_last_frame;
        InputBindingVector* binding;
    };

    class GamepadDevice
    {
    public:
        explicit GamepadDevice(SDL_Gamepad* gamepad);

        void process_device();
        void add_button_binding(SDL_GamepadButton button, InputBindingButton& bind);
        void add_axis_binding(SDL_GamepadAxis axis, InputBindingAxis& bind);
        void add_vector_binding(SDL_GamepadAxis axis_x, SDL_GamepadAxis axis_y, InputBindingVector& bind);

    private:
        std::vector<ButtonBinding> m_inputs_button;
        std::vector<AxisBinding>   m_inputs_axis;
        std::vector<VectorBinding> m_inputs_vector;
        SDL_Gamepad*               m_gamepad{};
    };
} // namespace stump
