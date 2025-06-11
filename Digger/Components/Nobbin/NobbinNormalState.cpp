#include "NobbinNormalState.h"

#include "../GridTransform.h"

#include <EngineTime.h>

std::unique_ptr<INobelState> NobbinNormalState::update(Nobbin& nobbin)
{
    const glm::vec2 out = nobbin.get_movement().get_current_state();

    if (glm::dot(out, out) > 0.1f)
    {
        if (m_move_delay < stump::EngineTime::instance().current_time)
        {
            m_move_delay = stump::EngineTime::instance().current_time + 0.1f;

            if (nobbin.get_grid_transform().can_move_direction(out))
            {
                nobbin.get_grid_transform().move(out);
                m_last_move_direction = out;
            }
            else
            {
                nobbin.get_grid_transform().move(m_last_move_direction);
            }
        }
    }

    return nullptr;
}