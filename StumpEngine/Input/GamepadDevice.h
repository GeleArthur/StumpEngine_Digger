#pragma once
#include "InputBinding.h"

#include <unordered_map>
#include <SDL3/SDL_gamepad.h>

namespace stump
{
    struct ButtonBindingGamepad final
    {
        SDL_GamepadButton   button;
        bool                pressed_last_frame;
        InputBindingButton* binding;
    };

    struct AxisBindingGamepad final
    {
        SDL_GamepadAxis   axis;
        Sint16            axis_last_frame;
        bool              full_pressed;
        InputBindingAxis* binding;
    };

    struct VectorBindingGamepad final
    {
        SDL_GamepadAxis     axis_horizontal;
        SDL_GamepadAxis     axis_vertical;
        glm::vec2           axis_last_frame;
        InputBindingVector* binding;
    };

    struct VectorSidesBindingGamepad final
    {
        SDL_GamepadButton   y_up;
        SDL_GamepadButton   y_down;
        SDL_GamepadButton   x_left;
        SDL_GamepadButton   x_right;
        glm::vec2           axis_last_frame;
        InputBindingVector* binding;
    };

    class GamepadDevice final
    {
    public:
        explicit GamepadDevice(SDL_Gamepad* gamepad);

        void process_device();
        void add_button_binding(InputBindingButton& bind, SDL_GamepadButton button);
        void remove_button_binding(const InputBindingButton& bind);
        void add_axis_binding(InputBindingAxis& bind, SDL_GamepadAxis axis);
        void remove_axis_binding(const InputBindingAxis& bind);
        void add_vector_binding(InputBindingVector& bind, SDL_GamepadAxis axis_x, SDL_GamepadAxis axis_y);
        void remove_vector_binding(const InputBindingVector& bind);
        void add_vector_sides_binding(InputBindingVector& bind, SDL_GamepadButton y_up, SDL_GamepadButton y_down, SDL_GamepadButton x_left, SDL_GamepadButton x_right);
        void remove_vector_sides_binding(const InputBindingVector& bind);

    private:
        std::vector<ButtonBindingGamepad>      m_inputs_button;
        std::vector<AxisBindingGamepad>        m_inputs_axis;
        std::vector<VectorBindingGamepad>      m_inputs_vector;
        std::vector<VectorSidesBindingGamepad> m_inputs_vector_sides;
        SDL_Gamepad*                           m_gamepad{};
    };
} // namespace stump
