#include "DirtEraser.h"

#include "DirtEraser.h"

#include "DirtGrid.h"
#include "GridTransform.h"
#include <GameObject.h>
DirtEraser::DirtEraser(stump::GameObject& owner, DirtGrid& dirt_eraser)
    : Component{ owner }
    , m_grid_transform{ owner.get_component<GridTransform>() }
    , m_dirt_grid{ &dirt_eraser }
    , m_grid_moved{ [this](const glm::ivec2& direction) { erase_grid(direction); } }
{
    m_grid_transform->get_moved_event().add_listener(&m_grid_moved);
}

void DirtEraser::erase_grid(const glm::ivec2& direction) const
{
    glm::vec2 pos = m_grid_transform->get_real_position();
    m_dirt_grid->delete_on_texture(SDL_Rect{
        static_cast<int>(pos.x) - m_erase_size.x / 2,
        static_cast<int>(pos.y) - m_erase_size.x / 2,
        m_erase_size.x,
        m_erase_size.y });

    glm::ivec2 sub_pos = m_grid_transform->get_sub_position();

    if (std::abs(direction.x) > std::abs(direction.y))
    {
        if (sub_pos.x - direction.x == 0)
        {
            m_dirt_grid->clear_vertical_wall_between(m_grid_transform->get_grid_position(), m_grid_transform->get_grid_position() + direction);
        }
    }
    else
    {
        if (sub_pos.y - direction.y == 0)
        {
            m_dirt_grid->clear_horizontal_wall_between(m_grid_transform->get_grid_position(), m_grid_transform->get_grid_position() + direction);
        }
    }
}