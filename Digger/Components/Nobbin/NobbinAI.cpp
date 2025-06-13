#include "NobbinAI.h"

#include "Nobbin.h"
#include "../DirtGrid.h"
#include "../GridTransform.h"

#include <algorithm>
#include <array>
NobbinAI::NobbinAI(stump::GameObject& game_object, Nobbin& nobbin, GameDataTracker& game_data)
    : Component{ game_object }
    , m_nobbin{ (&nobbin) }
    , m_data_tracker(&game_data)
{
}
void NobbinAI::update()
{
    GridTransform& grid_transform = m_nobbin->get_grid_transform();

    if (grid_transform.can_move_any_direction())
    {
        auto& flow_field = m_data_tracker->get_flow_field();

        glm::ivec2 dir = flow_field[grid_transform.get_grid_position().x + grid_transform.get_grid_position().y * GridSettings::grid_tile_count.x].direction;
        m_nobbin->get_movement().update_binding(dir, false, false);
        m_last_move = dir;

        // std::array valid_directions{
        //     std::tuple{ false, glm::ivec2(0, -1), std::numeric_limits<float>::max() },
        //     std::tuple{ false, glm::ivec2(1, 0), std::numeric_limits<float>::max() },
        //     std::tuple{ false, glm::ivec2(0, 1), std::numeric_limits<float>::max() },
        //     std::tuple{ false, glm::ivec2(-1, 0), std::numeric_limits<float>::max() },
        // };
        // const glm::ivec2 position = grid_transform.get_grid_position();
        //
        // std::ranges::for_each(valid_directions, [&](auto& dir_tuple) {
        //     std::get<0>(dir_tuple) = !m_nobbin->get_dirt_grid().get_wall_between(position, position + std::get<1>(dir_tuple));
        // });
        //
        // GridTransform* clostest_player = *(std::ranges::min_element(m_data_tracker->get_players(), [&](GridTransform* player, GridTransform* player2) {
        //     return glm::length(glm::vec2{ player->get_grid_position() - position }) < glm::length(glm::vec2{ player2->get_grid_position() - position });
        // }));
        //
        // std::ranges::for_each(valid_directions, [&](auto& direction) {
        //     if (std::get<0>(direction))
        //     {
        //         std::get<2>(direction) = glm::length(glm::vec2{ (position + std::get<1>(direction)) - clostest_player->get_grid_position() });
        //     }
        // });
        //
        // auto result = std::ranges::min(valid_directions, [&](auto& e, auto& e1) {
        //     return std::get<2>(e) < std::get<2>(e1);
        // });
        //
        // m_last_move = std::get<1>(result);
        // m_nobbin->get_movement().update_binding(m_last_move, false, false);
    }
    else
    {
        m_nobbin->get_movement().update_binding(m_last_move, false, false);
    }
}