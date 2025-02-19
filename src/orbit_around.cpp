//
// Created by a on 19/02/2025.
//

#include "orbit_around.h"

#include "Minigin.h"

void OrbitAround::update()
{
    const float time = get_game_object().get_engine().get_time().current_time;

    m_transform->set_local_position({
        m_start_pos.x + (std::cos(time * m_orbit_speed) * m_orbit_size),
        m_start_pos.y + (std::sin(time * m_orbit_speed) * m_orbit_size),
    });
}
