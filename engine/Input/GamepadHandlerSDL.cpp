#include "GamepadHandler.h"

//TODO: LINUX Support not finished yet

class GamepadHandler::GamepadHandlerImpl
{
};


void GamepadHandler::poll_gamepad() const
{
}

void GamepadHandler::bind_gamepad_button(SDL_GamepadButton, input_pressed_type, std::unique_ptr<Command>&&) const
{
}

void GamepadHandler::unbind_gamepad_button(SDL_GamepadButton, input_pressed_type) const
{
}


GamepadHandler::GamepadHandler():
    m_handler_imlp{std::make_unique<GamepadHandlerImpl>()}
{
}

GamepadHandler::~GamepadHandler() = default;


