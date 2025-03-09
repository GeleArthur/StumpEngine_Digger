#include "GamepadHandler.h"

//TODO: LINUX Support not finished yet

class GamepadHandler::GamepadHandlerImpl
{
};


void GamepadHandler::poll_gamepad() const
{
}

void GamepadHandler::bind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type, std::unique_ptr<Command>&& command) const
{
}

GamepadHandler::GamepadHandler():
    m_handler_imlp{std::make_unique<GamepadHandlerImpl>()}
{
}

GamepadHandler::~GamepadHandler() = default;


