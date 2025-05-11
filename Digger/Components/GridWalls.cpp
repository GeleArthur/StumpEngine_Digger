#include "GridWalls.h"

#include <stdexcept>

GridWalls::GridWalls(GameObject& game_object)
    : Component{ game_object }
{
    for (auto& walls : m_horizonal_walls)
        for (bool& wall : walls)
            wall = true;

    for (auto& walls : m_vertical_walls)
        for (bool& wall : walls)
            wall = true;
}
void GridWalls::render(SDL_Renderer* renderer)
{
    for (int x = 0; x < m_horizonal_walls.size(); ++x)
    {
        for (int y = 0; y < m_horizonal_walls[y].size(); ++y)
        {
            if (m_horizonal_walls[x][y])
            {
                SDL_RenderLine(renderer,
                               static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x),
                               static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y),
                               static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x + GridSettings::grid_tile_pixel_size.x),
                               static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y));
            }
        }
    }

    for (int x = 0; x < m_vertical_walls.size(); ++x)
    {
        for (int y = 0; y < m_vertical_walls[y].size(); ++y)
        {
            if (m_vertical_walls[x][y])
            {
                SDL_RenderLine(renderer,
                               static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x),
                               static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y),
                               static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x),
                               static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y + GridSettings::grid_tile_pixel_size.y));
            }
        }
    }
}

Walls GridWalls::get_walls(int x, int y) const
{
    if (x > GridSettings::grid_tile_count.x || x < 0 || y > GridSettings::grid_tile_count.y || y < 0)
        throw std::out_of_range("Out of bounds");

    return Walls{
        m_horizonal_walls[y][x],
        m_vertical_walls[y][x + 1],
        m_horizonal_walls[y][x],
        m_vertical_walls[y + 1][x],
    };
}
