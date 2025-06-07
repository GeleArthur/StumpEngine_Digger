#pragma once

#include <memory>
#include <span>
#include <vector>

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>

#include "GamePadEnums.h"
#include "GamepadHandler.h"

#include <Command.h>

namespace stump
{
    class CommandAxis2D;
    class CommandAxis;

    struct KeyboardInputSignature
    {
        SDL_Scancode       key_code;
        input_pressed_type input_type;
        bool               previous_performed;
    };

    class InputHandler final
    {
    public:
        explicit InputHandler();

        void process_input();
        void bind_keyboard(SDL_Scancode key_code, input_pressed_type input_type, std::unique_ptr<Command>&& command);
        void bind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type, std::unique_ptr<Command>&& command) const;
        void unbind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type) const;
        void unbind_keyboard(SDL_Scancode key_code, input_pressed_type input_type);

    private:
        std::span<const bool>                                                     m_sdl_keyboard_state;
        std::vector<std::tuple<KeyboardInputSignature, std::unique_ptr<Command>>> m_keyboard_bindings;
        GamepadHandler                                                            m_gamepad_handler;
    };
} // namespace stump
