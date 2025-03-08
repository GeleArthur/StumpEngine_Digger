//
// Created by a on 06/03/2025.
//

#include "InputHandler.h"

#include <span>
#include <tuple>
#include <SDL3/SDL_events.h>


InputHandler::InputHandler()
{
    int count{};
    const bool* thing = SDL_GetKeyboardState(&count);
    m_sdl_keyboard_state = std::span(thing, count); // is there a better way to init this?
}

void InputHandler::process_input()
{
    for (auto& keyboard_binding : m_keyboard_bindings)
    {
        KeyboardInputSignature& keyboard_input = std::get<0>(keyboard_binding);
        switch (keyboard_input.input_type)
        {
        case input_pressed_type::pressed_this_frame:
            if (!keyboard_input.previous_performed && m_sdl_keyboard_state[keyboard_input.key_code])
            {
                std::get<1>(keyboard_binding)->execute();
            }
            break;
        case input_pressed_type::held_down:
            if (m_sdl_keyboard_state[keyboard_input.key_code])
            {
                std::get<1>(keyboard_binding)->execute();
            }
            break;
        case input_pressed_type::let_go_this_frame:
            if (keyboard_input.previous_performed && !m_sdl_keyboard_state[keyboard_input.key_code])
            {
                std::get<1>(keyboard_binding)->execute();
            }
            break;
        }
        keyboard_input.previous_performed = m_sdl_keyboard_state[keyboard_input.key_code];
    }
}

// Template???
void InputHandler::bind_keyboard(const KeyboardInputSignature& keyboard_input_signature, std::unique_ptr<Command>&& command)
{
    m_keyboard_bindings.emplace_back(keyboard_input_signature, std::move(command));
}

void InputHandler::bind_gamepad_button(const GamepadButtonSignature& gamepad_button, std::unique_ptr<Command> command)
{
    m_gamepad_button_bindings.emplace_back(gamepad_button, std::move(command));
}

void InputHandler::bind_gamepad_axis(const GamepadAxisSignature& gamepad_axis, std::unique_ptr<CommandAxis> command)
{
    m_gamepad_axis_bindings.emplace_back(gamepad_axis, std::move(command));
}

void InputHandler::bind_gamepad_axis2d(const GamepadAxis2DSignature& gamepad_axis2d, std::unique_ptr<CommandAxis2D> command)
{
    m_gamepad_axis2d_bindings.emplace_back(gamepad_axis2d, std::move(command));
}
