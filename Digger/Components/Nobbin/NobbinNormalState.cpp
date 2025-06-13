#include "NobbinNormalState.h"

#include "Nobbin.h"
#include "NobbinDrillerState.h"
#include "../DirtGrid.h"
#include "../GridTransform.h"

#include <EngineTime.h>
#include <Component/Texture2DSpriteSheet.h>

NobbinNormalState::NobbinNormalState(Nobbin& nobbin)
    : m_nobbin{ &nobbin }
{
}

std::unique_ptr<INobbinState> NobbinNormalState::update()
{
    if (m_time_before_transform < stump::EngineTime::instance().get_current_time())
    {
        return std::make_unique<NobbinDrillerState>(*m_nobbin);
    }

    m_nobbin->get_sprite_sheet().set_sprite_index({ 0, 0 });

    const glm::vec2 direction = m_nobbin->get_movement().get_current_state();

    if (glm::dot(direction, direction) < 0.1f)
        return nullptr;

    if (m_move_delay >= stump::EngineTime::instance().get_current_time())
        return nullptr;

    m_move_delay = stump::EngineTime::instance().get_current_time() + 0.1f;

    glm::ivec2 direction_grid = GridTransform::free_direction_to_grid_direction(direction);

    if (m_nobbin->get_grid_transform().can_move_direction(direction_grid))
        m_last_move_direction = direction_grid;

    if (m_nobbin->get_grid_transform().can_move_any_direction())
    {
        glm::ivec2 grid_pos = m_nobbin->get_grid_transform().get_grid_position();
        if (!m_nobbin->get_dirt_grid().get_wall_between(grid_pos, grid_pos + m_last_move_direction))
        {
            m_nobbin->get_grid_transform().move(m_last_move_direction);
        }
    }
    else
    {
        m_nobbin->get_grid_transform().move(m_last_move_direction);
    }

    return nullptr;
}
bool NobbinNormalState::can_mine()
{
    return false;
}
