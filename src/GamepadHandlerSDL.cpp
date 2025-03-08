#include "GamepadHandler.h"


class GamepadHandler::XInputHandlerImlp
{
public:
    void poll_gamepad_impl();
};

void GamepadHandler::XInputHandlerImlp::poll_gamepad_impl()
{
}


void GamepadHandler::poll_gamepad()
{
    m_handler_imlp->poll_gamepad_impl();
}
