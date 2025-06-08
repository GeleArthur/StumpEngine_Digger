#pragma once
#include "GamepadDevice.h"
#include "KeyboardDevice.h"
namespace stump
{
    class InputManager
    {
    public:
        static InputManager& instance();
        void                 fetch_devices();
        void                 process_input();

        std::vector<GamepadDevice>& get_gamepads();
        KeyboardDevice&             get_keyboard();

    private:
        std::vector<GamepadDevice> m_gamepads;
        KeyboardDevice             m_keyboard{};
    };
} // namespace stump
