#include "NobbinNormalState.h"

#include "Nobbin.h"
#include "../DirtGrid.h"
#include "../GridTransform.h"

#include <EngineTime.h>

NobbinNormalState::NobbinNormalState(Nobbin& nobbin)
    : m_nobbin{ &nobbin }
{
}

std::unique_ptr<INobbinState> NobbinNormalState::update()
{
    const glm::vec2 direction = m_nobbin->get_movement().get_current_state();

    if (glm::dot(direction, direction) < 0.1f)
        return nullptr;

    if (m_move_delay >= stump::EngineTime::instance().current_time)
        return nullptr;

    m_move_delay = stump::EngineTime::instance().current_time + 0.1f;

    glm::ivec2 direction_grid = GridTransform::free_direction_to_grid_direction(direction);

    if (m_nobbin->get_grid_transform().can_move_direction(direction_grid))
        m_last_move_direction = direction_grid;

    if (m_nobbin->get_grid_transform().can_move_any_direction())
    {
        if (!check_wall(m_last_move_direction))
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

bool NobbinNormalState::check_wall(glm::ivec2 direction) const
{
    DirtGrid& dirt_grid = m_nobbin->get_dirt_grid();

    bool wall = dirt_grid.get_wall_between(m_nobbin->get_grid_transform().get_grid_position(), m_nobbin->get_grid_transform().get_grid_position() + direction);

    return wall;
}