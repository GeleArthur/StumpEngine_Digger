#include "GamepadHandler.h"

#include <vector>
#include <windows.h>
#include <xinput.h>

#pragma comment(lib, "xinput.lib")

#include "Command.h"
#include "GamePadEnums.h"

struct GamepadButtonSignature
{
    uint16_t gamepad_button;
    input_pressed_type input_type;
};

struct GamepadAxisSignature
{
    uint16_t gamepad_axis;
    input_pressed_type input_type;
};

struct GamepadAxis2DSignature
{
    uint16_t gamepad_axis2d;
    input_pressed_type input_type;
};

uint16_t sdl_gamepad_to_xinput(SDL_GamepadButton gamepad_button)
{
    switch (gamepad_button)
    {
    case SDL_GAMEPAD_BUTTON_SOUTH:
        return XINPUT_GAMEPAD_A;
    case SDL_GAMEPAD_BUTTON_EAST:
        return XINPUT_GAMEPAD_B;
    case SDL_GAMEPAD_BUTTON_WEST:
        return XINPUT_GAMEPAD_X;
    case SDL_GAMEPAD_BUTTON_NORTH:
        return XINPUT_GAMEPAD_Y;
    case SDL_GAMEPAD_BUTTON_BACK:
        return XINPUT_GAMEPAD_BACK;
    case SDL_GAMEPAD_BUTTON_START:
        return XINPUT_GAMEPAD_START;
    case SDL_GAMEPAD_BUTTON_LEFT_STICK:
        return XINPUT_GAMEPAD_LEFT_THUMB;
    case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
        return XINPUT_GAMEPAD_RIGHT_THUMB;
    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
        return XINPUT_GAMEPAD_LEFT_SHOULDER;
    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
        return XINPUT_GAMEPAD_RIGHT_SHOULDER;
    case SDL_GAMEPAD_BUTTON_DPAD_UP:
        return XINPUT_GAMEPAD_DPAD_UP;
    case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
        return XINPUT_GAMEPAD_DPAD_DOWN;
    case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
        return XINPUT_GAMEPAD_DPAD_LEFT;
    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
        return XINPUT_GAMEPAD_DPAD_RIGHT;
    default:
        return 0;
    }
}

class GamepadHandler::GamepadHandlerImpl
{
public:
    void poll_gamepad_impl();
    void bind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type, std::unique_ptr<Command>&& command);
    void unbind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type);

    // void bind_gamepad_axis(const GamepadAxisSignature& gamepad_axis, std::unique_ptr<CommandAxis> command);
    // void bind_gamepad_axis2d(const GamepadAxis2DSignature& gamepad_axis2d, std::unique_ptr<CommandAxis2D> command);

private:
    XINPUT_GAMEPAD m_previous_xinput{};

    std::vector<std::tuple<GamepadButtonSignature, std::unique_ptr<Command>>> m_gamepad_button_bindings;
    // std::vector<std::tuple<GamepadAxisSignature, std::unique_ptr<CommandAxis>>> m_gamepad_axis_bindings;
    // std::vector<std::tuple<GamepadAxis2DSignature, std::unique_ptr<CommandAxis2D>>> m_gamepad_axis2d_bindings;
};

void GamepadHandler::GamepadHandlerImpl::poll_gamepad_impl()
{
    XINPUT_STATE state{};
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        for (auto& element : m_gamepad_button_bindings)
        {
            auto& input_settings = std::get<0>(element);

            switch (input_settings.input_type)
            {
            case input_pressed_type::pressed_this_frame:
                if ((m_previous_xinput.wButtons & input_settings.gamepad_button) == 0 &&
                    ((state.Gamepad.wButtons & input_settings.gamepad_button) != 0))
                {
                    std::get<1>(element)->execute();
                }
                break;
            case input_pressed_type::held_down:
                if ((state.Gamepad.wButtons & input_settings.gamepad_button) != 0)
                {
                    std::get<1>(element)->execute();
                }
                break;
            case input_pressed_type::let_go_this_frame:
                if ((m_previous_xinput.wButtons & input_settings.gamepad_button) != 0 &&
                    ((state.Gamepad.wButtons & input_settings.gamepad_button) == 0))
                {
                    std::get<1>(element)->execute();
                }
                break;
            }
        }

        m_previous_xinput = state.Gamepad;
    }
}

void GamepadHandler::GamepadHandlerImpl::bind_gamepad_button(const SDL_GamepadButton gamepad_button, const input_pressed_type input_type, std::unique_ptr<Command>&& command)
{
    const uint16_t xinput_button = sdl_gamepad_to_xinput(gamepad_button);
    if (xinput_button == 0)
    {
        return;
    }

    m_gamepad_button_bindings.emplace_back(GamepadButtonSignature{xinput_button, input_type}, std::move(command));
}

void GamepadHandler::GamepadHandlerImpl::unbind_gamepad_button(const SDL_GamepadButton gamepad_button, const input_pressed_type input_type)
{
    const uint16_t xinput_button = sdl_gamepad_to_xinput(gamepad_button);

    std::erase_if(m_gamepad_button_bindings, [&](const std::tuple<GamepadButtonSignature, std::unique_ptr<Command>>& binding)
    {
        const auto& keyboard_info = std::get<0>(binding);
        return keyboard_info.gamepad_button == xinput_button && keyboard_info.input_type == input_type;
    });
}

// PUBLIC INTERFACE

GamepadHandler::GamepadHandler(): m_handler_imlp{std::make_unique<GamepadHandlerImpl>()}
{
}

GamepadHandler::~GamepadHandler() = default;

void GamepadHandler::poll_gamepad() const
{
    m_handler_imlp->poll_gamepad_impl();
}

void GamepadHandler::bind_gamepad_button(const SDL_GamepadButton gamepad_button, const input_pressed_type input_type, std::unique_ptr<Command>&& command) const
{
    m_handler_imlp->bind_gamepad_button(gamepad_button, input_type, std::move(command));
}

void GamepadHandler::unbind_gamepad_button(const SDL_GamepadButton gamepad_button, const input_pressed_type input_type) const
{
    m_handler_imlp->unbind_gamepad_button(gamepad_button, input_type);
}
