#include "GoldBagCollectable.h"

#include "GoldBag.h"
#include "../ColliderGrid.h"

#include <EngineTime.h>
#include <GameObject.h>
#include <Component/Texture2DSpriteSheet.h>

std::unique_ptr<IGoldBagState> GoldBagCollectable::update(GoldBag& bag)
{
    if (m_colleted > 0)
    {
        bag.get_game_object().mark_for_deletion();
    }

    if (m_sprite_index < 2)
    {
        if (m_animation_delay <= stump::EngineTime::instance().get_current_time())
        {
            ++m_sprite_index;
            m_animation_delay = stump::EngineTime::instance().get_current_time() + 0.1f;
        }
    }

    bag.get_sprite_sheet().set_sprite_index({ m_sprite_index, 1 });

    return nullptr;
}

void GoldBagCollectable::collided(ColliderGrid& tag, glm::ivec2 direction)
{
    if (tag.get_tag() == 0)
    {
        m_colleted = 1;
    }
    if (tag.get_tag() == 1)
    {
        m_colleted = 2;
    }
}