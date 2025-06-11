#pragma once
#include <EventListener.h>
#include <vec2.hpp>
#include <Component/Component.h>

class DirtGrid;
class GridTransform;
class DirtEraser final : public stump::Component
{
public:
    explicit DirtEraser(stump::GameObject& owner, DirtGrid& dirt_eraser);
    void erase_grid(const glm::ivec2& direction) const;
    void set_erase_size(const glm::ivec2 size)
    {
        m_erase_size = size;
    }

private:
    GridTransform*                   m_grid_transform;
    DirtGrid*                        m_dirt_grid;
    stump::EventListener<glm::ivec2> m_grid_moved;
    glm::ivec2                       m_erase_size{ 17 * 3, 18 * 3 };
};
