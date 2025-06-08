#include "InputManager.h"

namespace stump
{
    InputManager& InputManager::instance()
    {
        static InputManager input;
        return input;
    }
    void InputManager::fetch_devices()
    {
        m_gamepads.clear();

        int             count;
        SDL_JoystickID* joysticks = SDL_GetGamepads(&count);

        for (int i = 0; i < count; ++i)
        {
            SDL_Gamepad* gamepad = SDL_OpenGamepad(joysticks[i]);
            if (gamepad == nullptr)
                continue;

            m_gamepads.emplace_back(gamepad);
        }
    }

    void InputManager::process_input()
    {
        m_keyboard.process_device();
        for (GamepadDevice& gamepad : m_gamepads)
        {
            gamepad.process_device();
        }
    }
    std::vector<GamepadDevice>& InputManager::get_gamepads()
    {
        return m_gamepads;
    }
    KeyboardDevice& InputManager::get_keyboard()
    {
        return m_keyboard;
    }
} // namespace stump