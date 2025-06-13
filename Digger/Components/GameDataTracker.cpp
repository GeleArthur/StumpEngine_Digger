#include "GameDataTracker.h"
#include <queue>

GameDataTracker::GameDataTracker(stump::GameObject& attached, DirtGrid& grid)
    : Component{ attached }
    , m_grid{ &grid }
{
}
void GameDataTracker::update()
{
    update_flow_field();
}
void GameDataTracker::update_flow_field()
{
    constexpr std::array<glm::ivec2, 4> directions = {
        glm::ivec2{ 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 }
    };

    std::queue<glm::ivec2> queue;
    for (Cell& cel : m_flow_field)
    {
        cel.cost = std::numeric_limits<int>::max();
    }

    for (GridTransform* player : m_players)
    {
        m_flow_field[player->get_grid_position().x + player->get_grid_position().y * GridSettings::grid_tile_count.x].cost = 0;
        queue.push(player->get_grid_position());
    }

    while (!queue.empty())
    {
        glm::ivec2 pos = queue.front();
        queue.pop();

        int curr_cost = m_flow_field[pos.x + pos.y * GridSettings::grid_tile_count.x].cost;

        for (glm::ivec2 dir : directions)
        {
            glm::ivec2 new_location = pos + dir;
            if (m_grid->get_wall_between(pos, new_location))
                continue;

            if (m_flow_field[new_location.x + new_location.y * GridSettings::grid_tile_count.x].cost > curr_cost + 1)
            {
                m_flow_field[new_location.x + new_location.y * GridSettings::grid_tile_count.x].cost = curr_cost + 1;
                queue.push({ new_location });
            }
        }
    }

    for (int i = 0; i < m_flow_field.size(); ++i)
    {
        glm::ivec2 location = { i % GridSettings::grid_tile_count.x, i / GridSettings::grid_tile_count.x };

        int        lowest_cost = std::numeric_limits<int>::max();
        glm::ivec2 best_dir{};

        for (glm::ivec2 direction : directions)
        {
            glm::ivec2 neighbor = location + direction;

            if (neighbor.x < 0 || neighbor.x > GridSettings::grid_tile_count.x - 1 ||
                neighbor.y < 0 || neighbor.y > GridSettings::grid_tile_count.y - 1)
                continue;

            if (m_flow_field[neighbor.x + neighbor.y * GridSettings::grid_tile_count.x].cost < lowest_cost)
            {
                lowest_cost = m_flow_field[neighbor.x + neighbor.y * GridSettings::grid_tile_count.x].cost;
                best_dir = direction;
            }
        }
        m_flow_field[location.x + location.y * GridSettings::grid_tile_count.x].direction = best_dir;
    }
}