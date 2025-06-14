#include "GoldBagPushed.h"

#include "GoldBag.h"
#include "GoldBagIdle.h"
#include "../GridTransform.h"

#include <EngineTime.h>

GoldBagPushed::GoldBagPushed(glm::ivec2 direction)
    : m_direction{ direction }
{
}
std::unique_ptr<IGoldBagState> GoldBagPushed::update(GoldBag& gold_bag)
{
    m_time_until_next_move -= stump::EngineTime::instance().get_delta_time();
    if (m_time_until_next_move < 0.0f)
    {
        m_time_until_next_move = 0.1f;
        gold_bag.get_grid_transform().move(m_direction);

        if (m_move_count-- < 0)
        {
            return std::make_unique<GoldBagIdle>();
        }
    }

    return nullptr;
}

void GoldBagPushed::collided(ColliderGrid&, glm::ivec2)
{
}
