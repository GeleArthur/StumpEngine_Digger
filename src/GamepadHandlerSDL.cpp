#include "GamepadHandler.h"

class GamepadHandler::GamepadHandlerImpl
{
};


void GamepadHandler::poll_gamepad() const
{
}

void GamepadHandler::bind_gamepad_button(uint16_t gamepad_button, input_pressed_type input_type, std::unique_ptr<Command>&& command) const
{
}

GamepadHandler::GamepadHandler():
    m_handler_imlp{std::make_unique<GamepadHandlerImpl>()}
{
}

GamepadHandler::~GamepadHandler() = default;


