#include "Digger.h"
#include "GridTransform.h"
#include <GameObject.h>
#include <imgui.h>
#include <Input/InputManager.h>

#include <vec2.hpp>
#include <EngineTime.h>
#include <Component/Texture2DSpriteSheet.h>

Digger::Digger(stump::GameObject& attached, const UseInput use_input, const bool player2)
    : Component{ attached }
    , m_player_moved([this](const glm::ivec2& dir) { player_moved(dir); })
    , m_grid_transform{ get_game_object().get_component<GridTransform>() }
    , m_sprite_sheet{ get_game_object().get_component<stump::Texture2DSpriteSheet>() }
    , m_other_color{ player2 }
    , m_use_input{ use_input }
{
    m_grid_transform->get_moved_event().add_listener(&m_player_moved);

    switch (use_input)
    {
        case UseInput::keyboard_and_gamepad:
            stump::InputManager::instance().get_keyboard().add_vector_binding(m_movement, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);
            for (stump::GamepadDevice& gamepad : stump::InputManager::instance().get_gamepads())
            {
                gamepad.add_vector_binding(m_movement, SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY);
                gamepad.add_vector_sides_binding(m_movement,
                                                 SDL_GAMEPAD_BUTTON_DPAD_UP,
                                                 SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                                 SDL_GAMEPAD_BUTTON_DPAD_LEFT,
                                                 SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
            }
            break;
        case UseInput::keyboard:
            stump::InputManager::instance().get_keyboard().add_vector_binding(m_movement, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);
            break;
        case UseInput::gamepad1: {
            stump::GamepadDevice& gamepad = stump::InputManager::instance().get_gamepads()[0];
            gamepad.add_vector_binding(m_movement, SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY);
            gamepad.add_vector_sides_binding(m_movement,
                                             SDL_GAMEPAD_BUTTON_DPAD_UP,
                                             SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                             SDL_GAMEPAD_BUTTON_DPAD_LEFT,
                                             SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
        }
        break;
        case UseInput::gamepad2: {
            stump::GamepadDevice& gamepad = stump::InputManager::instance().get_gamepads()[1];
            gamepad.add_vector_binding(m_movement, SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY);
            gamepad.add_vector_sides_binding(m_movement,
                                             SDL_GAMEPAD_BUTTON_DPAD_UP,
                                             SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                             SDL_GAMEPAD_BUTTON_DPAD_LEFT,
                                             SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
        }
        break;
        default:
            break;
    }

    if (!m_other_color)
    {
        m_sprite_sheet->set_sprite_index({ 0, 2 });
    }
    else
    {
        m_sprite_sheet->set_sprite_index({ 0, 0 });
    }
}
Digger::~Digger()
{
    switch (m_use_input)
    {
        case UseInput::keyboard_and_gamepad:
            stump::InputManager::instance().get_keyboard().remove_vector_binding(m_movement);
            for (stump::GamepadDevice& gamepad : stump::InputManager::instance().get_gamepads())
            {
                gamepad.remove_vector_binding(m_movement);
                gamepad.remove_vector_sides_binding(m_movement);
            }
            break;
        case UseInput::keyboard:
            stump::InputManager::instance().get_keyboard().remove_vector_binding(m_movement);
            break;
        case UseInput::gamepad1: {
            stump::GamepadDevice& gamepad = stump::InputManager::instance().get_gamepads()[0];
            gamepad.remove_vector_binding(m_movement);
            gamepad.remove_vector_sides_binding(m_movement);
        }
        break;
        case UseInput::gamepad2: {
            stump::GamepadDevice& gamepad = stump::InputManager::instance().get_gamepads()[1];
            gamepad.remove_vector_binding(m_movement);
            gamepad.remove_vector_sides_binding(m_movement);
        }
        break;
        default:
            break;
    }
}
void Digger::update()
{
    const glm::vec2 free_direction = m_movement.get_current_state();

    if (glm::dot(free_direction, free_direction) > 0.1f)
    {
        if (m_move_delay < stump::EngineTime::instance().get_current_time())
        {
            m_move_delay = stump::EngineTime::instance().get_current_time() + 0.1f;

            glm::ivec2 direction = GridTransform::free_direction_to_grid_direction(free_direction);

            if (m_grid_transform->can_move_direction(direction))
            {
                m_grid_transform->move(direction);
                m_last_move_direction = direction;
            }
            else
            {
                m_grid_transform->move(m_last_move_direction);
            }
        }
    }
}
void Digger::player_moved(const glm::ivec2& direction)
{
    if (!m_other_color)
    {
        m_sprite_sheet->set_sprite_index({ 0, 2 });
    }
    else
    {
        m_sprite_sheet->set_sprite_index({ 0, 0 });
    }

    if (std::abs(direction.x) > std::abs(direction.y))
    {
        m_sprite_sheet->set_rotation(0);
        m_sprite_sheet->set_flip_mode(direction.x > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    else
    {
        m_sprite_sheet->set_flip_mode(SDL_FLIP_NONE);
        m_sprite_sheet->set_rotation(direction.y > 0 ? -90.0f : 90.0f);
    }
}
