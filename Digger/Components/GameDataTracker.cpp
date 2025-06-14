#include "GameDataTracker.h"

#include "../Scene/Scenes.h"

#include <StumpEngine.h>
#include <queue>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>

GameDataTracker::GameDataTracker(stump::GameObject& attached, DirtGrid& grid)
    : Component{ attached }
    , m_grid{ &grid }
{
}
void GameDataTracker::player_dead()
{
    // this is doo doo
    write_to_json();
    get_game_object().get_engine().set_active_scene(Scenes::ui_scene(get_game_object().get_engine()));
}
void GameDataTracker::score_added(int amount)
{
    m_score += amount;
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

void GameDataTracker::write_to_json()
{
    std::ifstream  file("scores.json");
    nlohmann::json scores_json{};
    if (file.is_open())
    {
        scores_json = nlohmann::json::parse(file);
    }

    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 25);
    std::string                            random_word;
    for (int i = 0; i < 3; ++i)
        random_word += static_cast<char>('a' + dis(gen));

    scores_json["scores"][random_word] = m_score;

    std::ofstream output_file("scores.json");
    output_file << scores_json.dump();
    output_file.close();
}