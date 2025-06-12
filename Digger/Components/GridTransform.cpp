#include "GridTransform.h"

#include "DirtGrid.h"

#include <GameObject.h>
#include <cmath>
#include <Component/Transform.h>
GridTransform::GridTransform(stump::GameObject& attached, glm::ivec2 grid_position)
    : Component(attached)
    , m_grid_position{ grid_position }
    , m_sub_position{ 0, 0 }
{
}

void GridTransform::update()
{
    get_game_object().get_transform().set_local_position(get_real_position());
}

void GridTransform::move_horizontal(bool going_left)
{
    if (m_sub_position.y != 0)
        return;

    const int direction = going_left ? 1 : -1;

    if ((m_grid_position.x <= 0 && m_sub_position.x + direction < 0) ||
        (m_grid_position.x >= GridSettings::grid_tile_count.x - 1 && m_sub_position.x + direction > 0))
        return;

    m_sub_position.x += direction;
    if (std::abs(m_sub_position.x) > 2)
    {
        m_grid_position.x += direction;
        m_sub_position.x = -m_sub_position.x + direction;
    }
    m_moved.notify_listeners({ direction, 0 });
}
void GridTransform::move_vertical(bool going_down)
{
    if (m_sub_position.x != 0)
        return;

    const int direction = going_down ? 1 : -1;

    if ((m_grid_position.y <= 0 && m_sub_position.y + direction < 0) ||
        (m_grid_position.y >= GridSettings::grid_tile_count.y - 1 && m_sub_position.y + direction > 0))
        return;

    m_sub_position.y += direction;
    if (std::abs(m_sub_position.y) > 2)
    {
        m_grid_position.y += direction;
        m_sub_position.y = -m_sub_position.y + direction;
    }
    m_moved.notify_listeners({ 0, direction });
}
void GridTransform::move(const glm::ivec2& direction)
{
    if (std::abs(direction.x) > std::abs(direction.y))
    {
        move_horizontal(direction.x > 0.0f);
    }
    else
    {
        move_vertical(direction.y > 0.0f);
    }
}
bool GridTransform::can_move_direction(const glm::ivec2& direction) const
{
    if (std::abs(direction.x) > std::abs(direction.y))
    {
        return can_move_horizontal();
    }
    else
    {
        return can_move_vertical();
    }
}
bool GridTransform::can_move_any_direction() const
{
    return m_sub_position.x == 0 && m_sub_position.y == 0;
}
bool GridTransform::can_move_horizontal() const
{
    return m_sub_position.y == 0;
}
bool GridTransform::can_move_vertical() const
{
    return m_sub_position.x == 0;
}
glm::vec2 GridTransform::get_real_position() const
{
    return glm::vec2{
        GridSettings::grid_offset.x + m_grid_position.x * GridSettings::grid_tile_pixel_size.x + GridSettings::grid_tile_pixel_size.y / 2 + m_sub_position.x * GridSettings::grid_tile_pixel_size.x / 5,
        GridSettings::grid_offset.y + m_grid_position.y * GridSettings::grid_tile_pixel_size.y + GridSettings::grid_tile_pixel_size.x / 2 + m_sub_position.y * GridSettings::grid_tile_pixel_size.y / 5,
    };
}
glm::ivec2 GridTransform::free_direction_to_grid_direction(const glm::vec2& direction)
{
    return std::abs(direction.x) > std::abs(direction.y) ?
        glm::ivec2{ -(std::signbit(direction.x) * 2 - 1), 0 } :
        glm::ivec2{ 0, -(std::signbit(direction.y) * 2 - 1) };
}
stump::Event<glm::ivec2>& GridTransform::get_moved_event()
{
    return m_moved;
}