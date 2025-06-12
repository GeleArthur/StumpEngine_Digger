#pragma once

#include "INobbinState.h"

#include <Component/Component.h>
#include <Input/InputManager.h>
#include <memory>

class DirtGrid;
class GridTransform;
class Nobbin final : public stump::Component
{
public:
    explicit Nobbin(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid);
    virtual void update() override;

    const stump::InputBindingVector& get_movement() const
    {
        return m_movement;
    };

    GridTransform& get_grid_transform() const
    {
        return *m_grid_transform;
    }

    DirtGrid& get_dirt_grid() const
    {
        return *m_dirt_grid;
    }

private:
    stump::InputBindingVector m_movement;
    float                     m_move_delay{};
    GridTransform*            m_grid_transform;
    glm::vec2                 m_last_move_direction{};
    DirtGrid*                 m_dirt_grid;

    std::unique_ptr<INobbinState> m_state;
};
