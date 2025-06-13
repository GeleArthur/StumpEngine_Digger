#include "DirtGrid.h"

#include <GameObject.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <StumpEngine.h>
#include <span>

struct colors
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

DirtGrid::DirtGrid(stump::GameObject& attached_game_object, SDL_Renderer* renderer)
    : Component{ attached_game_object }
{
    const glm::ivec2 window_size = get_game_object().get_engine().get_window_size();
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, window_size.x, window_size.y);
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    colors* pixel_data{};
    int     pitch{};
    SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(&pixel_data), &pitch);

    for (int i = 0; i < m_texture->w * m_texture->h; ++i)
    {
        // // TODO: Wrong need to reworked as red and orange lines are not equal
        const int x = i % m_texture->w;
        const int y = i / m_texture->w;
        const int period = 6;

        const int stripe = y / period;
        const int y_in_stripe = y % period;

        const int   amplutide = 3;
        const float wave = amplutide + (std::sin(static_cast<float>(x * 0.4)) * amplutide);

        const bool above = y_in_stripe > wave;

        const bool use_first_color = above ^ (stripe & 1);

        pixel_data[i] = use_first_color ? colors{ 204, 0, 0 } : colors{ 204, 116, 0 };

        // pixel_data[i] = colors{ 204, 116, 0 };
    }
    SDL_UnlockTexture(m_texture);

    for (auto& walls : m_horizonal_walls)
        for (bool& wall : walls)
            wall = true;

    for (auto& walls : m_vertical_walls)
        for (bool& wall : walls)
            wall = true;
}

void DirtGrid::render(SDL_Renderer* renderer)
{
    const glm::ivec2& window_size = get_game_object().get_engine().get_window_size();
    const SDL_FRect   dst{ 0, 0, static_cast<float>(window_size.x), static_cast<float>(window_size.y) };
    SDL_RenderTexture(renderer, m_texture, nullptr, &dst);

    SDL_SetRenderDrawColor(renderer, 0, 255u, 0, 255);
    // for (int x = 0; x < m_horizonal_walls.size(); ++x)
    // {
    //     for (int y = 0; y < m_horizonal_walls[y].size(); ++y)
    //     {
    //         if (m_horizonal_walls[x][y])
    //         {
    //             SDL_RenderLine(renderer,
    //                            static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x),
    //                            static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y),
    //                            static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x + GridSettings::grid_tile_pixel_size.x),
    //                            static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y));
    //         }
    //     }
    // }
    //
    // for (int x = 0; x < m_vertical_walls.size(); ++x)
    // {
    //     for (int y = 0; y < m_vertical_walls[y].size(); ++y)
    //     {
    //         if (m_vertical_walls[x][y])
    //         {
    //             SDL_RenderLine(renderer,
    //                            static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x),
    //                            static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y),
    //                            static_cast<float>(GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x),
    //                            static_cast<float>(GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y + GridSettings::grid_tile_pixel_size.y));
    //         }
    //     }
    // }
}

void DirtGrid::update() {}

void DirtGrid::delete_on_texture(const SDL_Rect& rect) const
{
    colors* pixel_data{};
    int     pitch{};
    SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(&pixel_data), &pitch);

    const std::span mapped_data(pixel_data, m_texture->w * m_texture->h);
    for (int i = 0; i < rect.w * rect.h; ++i)
    {
        mapped_data[rect.x + rect.y * m_texture->w + (i % rect.w) + ((i / rect.w) * m_texture->w)] = colors{ 0, 0, 0 };
    }

    SDL_UnlockTexture(m_texture);
}
bool DirtGrid::get_wall_between(const glm::ivec2& from, const glm::ivec2& to) const
{
    if (
        from.x >= GridSettings::grid_tile_count.x || from.x < 0 ||
        from.y >= GridSettings::grid_tile_count.y || from.y < 0 ||
        to.x >= GridSettings::grid_tile_count.x || to.x < 0 ||
        to.y >= GridSettings::grid_tile_count.y || to.y < 0)
    {
        return true;
    }

    if (from.x == to.x)
    {
        return m_horizonal_walls.at(from.x).at(std::max(from.y, to.y));
    }
    else if (from.y == to.y)
    {
        return m_vertical_walls.at(std::max(from.x, to.x)).at(from.y);
    }

    assert("Can't go diagonal");

    return false;
}
void DirtGrid::clear_wall_between(const glm::ivec2& from, const glm::ivec2& to)
{
    if (from.x == to.x)
    {
        m_horizonal_walls.at(from.x).at(std::max(from.y, to.y)) = false;
    }
    else if (from.y == to.y)
    {
        m_vertical_walls.at(std::max(from.x, to.x)).at(from.y) = false;
    }

    assert("Can't go diagonal");
}
