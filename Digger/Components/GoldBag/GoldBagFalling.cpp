#include "GoldBagFalling.h"

#include "GoldBag.h"
#include "GoldBagCollectable.h"
#include "GoldBagIdle.h"
#include "../ColliderGrid.h"
#include "../DirtGrid.h"
#include "../GetHit.h"
#include "../GridTransform.h"

#include <EngineTime.h>
#include <GameObject.h>
#include <Component/Texture2DSpriteSheet.h>

std::unique_ptr<IGoldBagState> GoldBagFalling::update(GoldBag& gold_bag)
{
    if (m_start_delay >= stump::EngineTime::instance().get_current_time())
    {
        if (m_move_delay <= stump::EngineTime::instance().get_current_time())
        {
            m_animation_index = m_animation_index ? 0 : 2;
            m_move_delay = stump::EngineTime::instance().get_current_time() + 0.25f;
        }
        gold_bag.get_sprite_sheet().set_sprite_index({ m_animation_index, 0 });

        return nullptr;
    }

    if (m_move_delay >= stump::EngineTime::instance().get_current_time())
        return nullptr;

    gold_bag.get_sprite_sheet().set_sprite_index({ 1, 0 });

    m_move_delay = stump::EngineTime::instance().get_current_time() + 0.1f;

    glm::ivec2 grid_location = gold_bag.get_grid_transform().get_grid_position();

    if (gold_bag.get_grid_transform().can_move_any_direction())
    {
        ++m_blocks_fallen;
        if (gold_bag.get_dirt_grid().get_wall_between(grid_location, grid_location + glm::ivec2{ 0, 1 }) &&
            gold_bag.get_dirt_grid().get_wall_between(grid_location + glm::ivec2{ 0, 1 }, grid_location + glm::ivec2{ 1, 1 }) &&
            gold_bag.get_dirt_grid().get_wall_between(grid_location + glm::ivec2{ 0, 1 }, grid_location + glm::ivec2{ -1, 1 }))
        {
            if (m_blocks_fallen >= 3)
            {
                return std::make_unique<GoldBagCollectable>();
            }
            return std::make_unique<GoldBagIdle>();
        }
    }

    gold_bag.get_grid_transform().move(glm::ivec2{ 0, 1 });

    return nullptr;
}
void GoldBagFalling::collided(ColliderGrid& tag, glm::ivec2 direction)
{
    if (GetHit* thing = tag.get_game_object().get_component<GetHit>())
        thing->die();
}