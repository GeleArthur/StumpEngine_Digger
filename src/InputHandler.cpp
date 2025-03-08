//
// Created by a on 06/03/2025.
//

#include "InputHandler.h"
#include <tuple>

void InputHandler::process_input()
{
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
