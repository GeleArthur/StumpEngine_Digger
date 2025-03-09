#pragma once
#include <memory>
#include <SDL3/SDL_gamepad.h>

#include "Command.h"
#include "GamePadEnums.h"


class GamepadHandler final
{
public:
    ~GamepadHandler();


    GamepadHandler();
    void poll_gamepad() const;
    void bind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type, std::unique_ptr<Command>&& command) const;

private:
    class GamepadHandlerImpl;
    std::unique_ptr<GamepadHandlerImpl> m_handler_imlp;
};
