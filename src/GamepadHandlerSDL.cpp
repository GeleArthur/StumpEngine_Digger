#include "GamepadHandler.h"


class GamepadHandler::GamepadHandlerImpl
{
public:
    void poll_gamepad_impl();
};

void GamepadHandler::GamepadHandlerImpl::poll_gamepad_impl()
{
}


void GamepadHandler::poll_gamepad()
{
    m_handler_imlp->poll_gamepad_impl();
}
