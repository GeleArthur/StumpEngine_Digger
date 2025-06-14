#include "GoldBagIdle.h"

#include "GoldBag.h"
#include "GoldBagFalling.h"
#include "GoldBagPushed.h"
#include "../DirtGrid.h"
#include "../GridTransform.h"

#include <Component/Texture2DSpriteSheet.h>

// Idle state
std::unique_ptr<IGoldBagState> GoldBagIdle::update(GoldBag& gold_bag)
{
    gold_bag.get_sprite_sheet().set_sprite_index({ 0, 0 });

    if (m_swap_to_pushed)
    {
        return std::make_unique<GoldBagPushed>(m_direction);
    }

    glm::ivec2 grid_location = gold_bag.get_grid_transform().get_grid_position();
    if (
        !gold_bag.get_dirt_grid().get_wall_between(grid_location, grid_location + glm::ivec2{ 0, 1 }) ||
        !gold_bag.get_dirt_grid().get_wall_between(grid_location + glm::ivec2{ 0, 1 }, grid_location + glm::ivec2{ 1, 1 }) ||
        !gold_bag.get_dirt_grid().get_wall_between(grid_location + glm::ivec2{ 0, 1 }, grid_location + glm::ivec2{ -1, 1 }))
    {
        return std::make_unique<GoldBagFalling>();
    }

    return nullptr;
}
void GoldBagIdle::collided(ColliderGrid&, glm::ivec2 direction)
{
    if (direction.x == 0)
        return;
    m_direction = direction;
    m_swap_to_pushed = true;
}
