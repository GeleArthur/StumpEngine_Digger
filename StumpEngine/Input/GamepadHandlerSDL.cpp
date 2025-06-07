#include "GamepadHandler.h"

// TODO: LINUX Support not finished yet

class stump::GamepadHandler::GamepadHandlerImpl
{
};

void stump::GamepadHandler::poll_gamepad() const
{
}

void stump::GamepadHandler::bind_gamepad_button(SDL_GamepadButton, input_pressed_type, std::unique_ptr<Command>&&) const
{
}

void stump::GamepadHandler::unbind_gamepad_button(SDL_GamepadButton, input_pressed_type) const
{
}

stump::GamepadHandler::GamepadHandler()
    : m_handler_imlp{ std::make_unique<GamepadHandlerImpl>() }
{
}

stump::GamepadHandler::~GamepadHandler() = default;
