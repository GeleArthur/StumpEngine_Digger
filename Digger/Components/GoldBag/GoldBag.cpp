#include "GoldBag.h"

#include "GoldBagIdle.h"
#include "../GridTransform.h"

GoldBag::GoldBag(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid, stump::Texture2DSpriteSheet& sheet)
    : Component{ attached }
    , m_collided{ [this](const uint64_t tag, const glm::ivec2 direction) { m_current_state->collided(tag, direction); } }
    , m_grid_transform{ &grid_transform }
    , m_dirt_grid{ &dirt_grid }
    , m_sprite_sheet{ &sheet }
{
    m_current_state = std::make_unique<GoldBagIdle>();
}

void GoldBag::update()
{
    std::unique_ptr<IGoldBagState> new_state = m_current_state->update(*this);

    if (new_state.get() != nullptr)
    {
        m_current_state = std::move(new_state);
    }
}
