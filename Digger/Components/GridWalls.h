#pragma once
#include <array>
#include <vec2.hpp>
#include <vector>
#include <Component/Component.h>

// TODO: Wall based approce
struct Walls
{
    bool north;
    bool west;
    bool south;
    bool east;
};

namespace GridSettings
{
    constexpr static glm::ivec2 grid_tile_count{ 15, 10 };
    constexpr static glm::ivec2 grid_offset{ 16, 32 };
    constexpr static glm::ivec2 grid_tile_pixel_size{ 60, 50 };
} // namespace GridSettings

class GridWalls final : public stump::Component
{
public:
    explicit GridWalls(stump::GameObject& game_object);
    virtual void render(SDL_Renderer* renderer) override;

    [[nodiscard]] Walls get_walls(int x, int y) const;

private:
    std::array<std::array<bool, GridSettings::grid_tile_count.y + 1>, GridSettings::grid_tile_count.x> m_horizonal_walls{};
    std::array<std::array<bool, GridSettings::grid_tile_count.y>, GridSettings::grid_tile_count.x + 1> m_vertical_walls{};
};
