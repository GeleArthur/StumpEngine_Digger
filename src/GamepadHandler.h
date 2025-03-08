#pragma once
#include <memory>


class GamepadHandler
{
public:
    void poll_gamepad();

private:
    class GamepadHandlerImpl;
    std::unique_ptr<GamepadHandlerImpl> m_handler_imlp;
};
