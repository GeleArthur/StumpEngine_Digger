#include "NobbinSpawner.h"

#include "ColliderGrid.h"
#include "DirtEraser.h"
#include "GridTransform.h"
#include "Nobbin/Nobbin.h"
#include "Nobbin/NobbinAI.h"

#include <EngineTime.h>
#include <Scene.h>
#include <Component/Texture2DSpriteSheet.h>

NobbinSpawner::NobbinSpawner(stump::GameObject& attached,
                             stump::Scene&      scene,
                             DirtGrid&          grid,
                             CollisionHolder&   collision_holder,
                             GameDataTracker&   tracker,
                             const glm::ivec2   location,
                             const GameModes    mode,
                             const UseInput     input)
    : Component{ attached }
    , m_spawn_location{ location }
    , m_mode{ mode }
    , m_input{ input }
    , m_scene(&scene)
    , m_dirt{ &grid }
    , m_collision{ &collision_holder }
    , m_tracker{ &tracker }
{
}
void NobbinSpawner::update()
{
    if (m_timer_next_spawn < stump::EngineTime::instance().get_current_time())
    {
        m_timer_next_spawn = stump::EngineTime::instance().get_current_time() + 5.0f;

        // Urrggg Prototype pattern. But out of time :(
        stump::GameObject& nobbin = m_scene->add_game_object();
        auto&              sprite_sheet = nobbin.add_component<stump::Texture2DSpriteSheet>("data/SpritesEnemies.png").set_sprite_size({ 16, 15 }).set_size_multiplier(3);
        auto&              transform = nobbin.add_component<GridTransform>(m_spawn_location);
        auto&              nobbin_comp = nobbin.add_component<Nobbin>(transform, *m_dirt, sprite_sheet);
        nobbin.add_component<DirtEraser>(*m_dirt);
        nobbin.add_component<ColliderGrid>(transform, *m_collision, 1);

        if (m_mode == GameModes::versus && m_controlling_player == nullptr)
        {
            stump::GamepadDevice& gamepad = stump::InputManager::instance().get_gamepads()[m_input == UseInput::gamepad1 ? 0 : 1];
            gamepad.add_vector_binding(nobbin_comp.get_movement(), SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY);
            gamepad.add_vector_sides_binding(nobbin_comp.get_movement(),
                                             SDL_GAMEPAD_BUTTON_DPAD_UP,
                                             SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                             SDL_GAMEPAD_BUTTON_DPAD_LEFT,
                                             SDL_GAMEPAD_BUTTON_DPAD_RIGHT);

            m_controlling_player = &nobbin_comp;
        }
        else
        {
            nobbin.add_component<NobbinAI>(nobbin_comp, *m_tracker);
        }
    }
}