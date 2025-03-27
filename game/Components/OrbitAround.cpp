#include "OrbitAround.h"

#include <Minigin.h>

void OrbitAround::update()
{
    const float time = get_game_object().get_engine().get_time().current_time;

    m_transform->set_local_position({
        (std::cos(time * m_orbit_speed) * m_orbit_size),
        (std::sin(time * m_orbit_speed) * m_orbit_size),
    });
}
