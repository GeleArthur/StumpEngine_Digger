#pragma once
#include "GamepadDevice.h"
#include "KeyboardDevice.h"

#include <Singleton.h>
namespace stump
{
    class InputManager : public Singleton<InputManager>
    {
    public:
        void fetch_devices();
        void process_input();

        std::vector<GamepadDevice>& get_gamepads();
        KeyboardDevice&             get_keyboard();

    private:
        std::vector<GamepadDevice> m_gamepads;
        KeyboardDevice             m_keyboard{};

        friend Singleton;
        InputManager() = default;
    };
} // namespace stump
