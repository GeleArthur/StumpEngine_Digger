#pragma once
#include <memory>


class GamepadHandler
{
public:
    void poll_gamepad();

private:
    class XInputHandlerImlp;
    std::unique_ptr<XInputHandlerImlp> m_handler_imlp;
};
