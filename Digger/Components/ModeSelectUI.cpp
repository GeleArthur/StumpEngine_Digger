#include "ModeSelectUI.h"

#include "GridTransform.h"
#include "../Scenes.h"

#include <GameObject.h>
#include <Scene.h>
#include <StumpEngine.h>
#include <Component/Texture2D.h>
#include <Input/InputManager.h>
ModeSelectUi::ModeSelectUi(stump::GameObject& attached, stump::Scene& scene)
    : Component{ attached }
    , m_move{ [this](const glm::vec2 direction) { pressed(direction); } }
    , m_press_start{ [this] { start_game(); } }
{
    auto& game_object = scene.add_game_object();
    m_arrow_transform = &game_object.get_transform();
    m_arrow_transform->set_local_position({ 500, 210 });
    game_object.add_component<stump::Texture2D>("data/arrow.png");

    stump::InputManager::instance().get_keyboard().add_vector_binding(m_move_cursor, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);
    stump::InputManager::instance().get_keyboard().add_button_binding(m_game_start, SDL_SCANCODE_SPACE);
    for (stump::GamepadDevice& gamepad : stump::InputManager::instance().get_gamepads())
    {
        gamepad.add_vector_binding(m_move_cursor, SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY);
        gamepad.add_vector_sides_binding(m_move_cursor, SDL_GAMEPAD_BUTTON_DPAD_UP, SDL_GAMEPAD_BUTTON_DPAD_DOWN, SDL_GAMEPAD_BUTTON_DPAD_LEFT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
        gamepad.add_button_binding(m_game_start, SDL_GAMEPAD_BUTTON_SOUTH);
    }

    m_game_start.get_on_pressed()->add_listener(&m_press_start);

    m_move_cursor.on_pressed()->add_listener(&m_move);
}
void ModeSelectUi::pressed(const glm::vec2 direction)
{
    auto dir = GridTransform::free_direction_to_grid_direction(direction);

    if (dir.y < 0)
    {
        int new_mode = static_cast<int>(m_selected_game_mode) - 1;
        if (new_mode < 0)
        {
            new_mode = static_cast<int>(GameModes::count) - 1;
        }
        m_selected_game_mode = static_cast<GameModes>(new_mode);
    }
    else
    {
        m_selected_game_mode = static_cast<GameModes>((static_cast<int>(m_selected_game_mode) + 1) % static_cast<int>(GameModes::count));
    }

    m_arrow_transform->set_local_position(glm::vec2{ 500, 210 + static_cast<int>(m_selected_game_mode) * 100 });
}
void ModeSelectUi::start_game()
{
    get_game_object().get_engine().set_active_scene(Scenes::level_scene(get_game_object().get_engine()));
}
