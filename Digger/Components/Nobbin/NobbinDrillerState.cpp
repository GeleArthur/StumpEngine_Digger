#include "NobbinDrillerState.h"

#include "Nobbin.h"
#include "../DirtGrid.h"
#include "../GridTransform.h"

#include <EngineTime.h>
#include <Component/Texture2DSpriteSheet.h>
NobbinDrillerState::NobbinDrillerState(Nobbin& nobbin)
    : m_nobbin{ &nobbin }
{
}
std::unique_ptr<INobbinState> NobbinDrillerState::update()
{
    m_nobbin->get_sprite_sheet().set_sprite_index({ 0, 1 });

    const glm::vec2 direction = m_nobbin->get_movement().get_current_state();

    if (glm::dot(direction, direction) < 0.1f)
        return nullptr;

    if (m_move_delay >= stump::EngineTime::instance().current_time)
        return nullptr;

    m_move_delay = stump::EngineTime::instance().current_time + 0.1f;

    glm::ivec2 direction_grid = GridTransform::free_direction_to_grid_direction(direction);

    if (m_nobbin->get_grid_transform().can_move_direction(direction_grid))
        m_last_move_direction = direction_grid;

    if (m_nobbin->get_grid_transform().can_move_any_direction())
    {
        m_nobbin->get_grid_transform().move(m_last_move_direction);
    }
    else
    {
        m_nobbin->get_grid_transform().move(m_last_move_direction);
    }

    look_direction(m_last_move_direction);

    return nullptr;
}
void NobbinDrillerState::look_direction(glm::ivec2 direction)
{
    if (std::abs(direction.x) > std::abs(direction.y))
    {
        m_nobbin->get_sprite_sheet().set_flip_mode(direction.x > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
}
