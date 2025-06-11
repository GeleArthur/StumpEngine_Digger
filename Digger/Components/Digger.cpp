#include "Digger.h"
#include "GridTransform.h"
#include <GameObject.h>
#include <imgui.h>
#include <Input/InputManager.h>

#include <vec2.hpp>
#include <EngineTime.h>
#include <Component/Texture2DSpriteSheet.h>

Digger::Digger(stump::GameObject& attached)
    : Component{ attached }
    , m_player_moved([this](const glm::ivec2& dir) { player_moved(dir); })
    , m_grid_transform{ get_game_object().get_component<GridTransform>() }
    , m_sprite_sheet{ get_game_object().get_component<stump::Texture2DSpriteSheet>() }
{
    m_grid_transform->get_moved_event().add_listener(&m_player_moved);
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
}
void Digger::update()
{
    const glm::vec2 out = m_movement.get_current_state();

    if (glm::dot(out, out) > 0.1f)
    {
        if (m_move_delay < stump::EngineTime::instance().current_time)
        {
            m_move_delay = stump::EngineTime::instance().current_time + 0.1f;

            if (m_grid_transform->can_move_direction(out))
            {
                m_grid_transform->move(out);
                m_last_move_direction = out;
            }
            else
            {
                m_grid_transform->move(m_last_move_direction);
            }
        }
    }
}
void Digger::render(SDL_Renderer* renderer)
{
}
void Digger::player_moved(const glm::ivec2& direction)
{
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
