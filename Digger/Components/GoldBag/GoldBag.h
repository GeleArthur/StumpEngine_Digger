#pragma once

#include "IGoldBagState.h"

#include <EventListener.h>
#include <memory>
#include <vec2.hpp>
#include <Component/Component.h>

namespace stump
{
    class Texture2DSpriteSheet;
}
class DirtGrid;
class GridTransform;
class GoldBag final : public stump::Component
{
public:
    explicit GoldBag(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid, stump::Texture2DSpriteSheet& sheet);
    void update() override;

    GridTransform& get_grid_transform() const
    {
        return *m_grid_transform;
    }

    DirtGrid& get_dirt_grid() const
    {
        return *m_dirt_grid;
    }

    stump::Texture2DSpriteSheet& get_sprite_sheet() const
    {
        return *m_sprite_sheet;
    }

private:
    std::unique_ptr<IGoldBagState>             m_current_state{};
    stump::EventListener<uint64_t, glm::ivec2> m_collided;
    GridTransform*                             m_grid_transform;
    DirtGrid*                                  m_dirt_grid;
    stump::Texture2DSpriteSheet*               m_sprite_sheet;
};
