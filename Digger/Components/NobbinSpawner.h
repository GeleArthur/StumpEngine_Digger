#pragma once
#include "CollisionHolder.h"
#include "DirtGrid.h"
#include "GameDataTracker.h"
#include "../GameModes.h"

#include <EngineTime.h>
#include <vec2.hpp>
#include <Component/Component.h>

class Nobbin;
namespace stump
{
    class Scene;
}
class NobbinSpawner : public stump::Component
{
public:
    explicit NobbinSpawner(stump::GameObject& attached,
                           stump::Scene&      scene,
                           DirtGrid&          grid,
                           CollisionHolder&   collision_holder,
                           GameDataTracker&   tracker,
                           glm::ivec2         location,
                           GameModes          mode,
                           UseInput           input);

    void update() override;

private:
    float            m_timer_next_spawn{ stump::EngineTime::instance().get_current_time() + 2.5f };
    glm::ivec2       m_spawn_location;
    GameModes        m_mode;
    UseInput         m_input;
    stump::Scene*    m_scene;
    DirtGrid*        m_dirt;
    CollisionHolder* m_collision;
    GameDataTracker* m_tracker;

    Nobbin* m_controlling_player{};
};
