#pragma once

#include "INobbinState.h"

#include <EngineTime.h>
#include <Component/Component.h>
#include <Input/InputManager.h>
#include <memory>

namespace stump
{
    class Texture2DSpriteSheet;
}

class DirtGrid;
class GridTransform;
class Nobbin final : public stump::Component
{
public:
    explicit Nobbin(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid, stump::Texture2DSpriteSheet& sprite_sheet);
    ~Nobbin() override;
    void update() override;

    [[nodiscard]] stump::InputBindingVector& get_movement()
    {
        return m_movement;
    };

    [[nodiscard]] GridTransform& get_grid_transform() const
    {
        return *m_grid_transform;
    }

    [[nodiscard]] DirtGrid& get_dirt_grid() const
    {
        return *m_dirt_grid;
    }

    [[nodiscard]] stump::Texture2DSpriteSheet& get_sprite_sheet() const
    {
        return *m_sprite_sheet;
    }

    [[nodiscard]] INobbinState& get_current_state() const
    {
        return *m_state.get();
    }

private:
    stump::InputBindingVector    m_movement;
    stump::InputBindingButton    m_transform;
    float                        m_move_delay{};
    GridTransform*               m_grid_transform;
    glm::vec2                    m_last_move_direction{};
    DirtGrid*                    m_dirt_grid;
    stump::Texture2DSpriteSheet* m_sprite_sheet;

    std::unique_ptr<INobbinState> m_state;
};
