#include "LevelScene.h"
#include <memory>

#include "Components/DirtEraser.h"
#include "Components/DirtGrid.h"
#include "Components/GoldBag.h"
#include "Components/GridTransform.h"
#include "Components/Nobbin/Nobbin.h"

#include <GameObject.h>
#include <StumpEngine.h>
#include <fstream>
#include <Component/FpsShowCase.h>
#include <Component/TextDisplay.h>
#include <Component/Texture2DSpriteSheet.h>
#include <nlohmann/json.hpp>

std::unique_ptr<stump::Scene> Scenes::level_scene(stump::StumpEngine& engine)
{
    auto        scene = std::make_unique<stump::Scene>(engine);
    const auto& level_holder = scene->add_game_object();

    std::ifstream  f("data/level1.json");
    nlohmann::json level_json = nlohmann::json::parse(f);

    std::vector<int> grid_array = level_json["grid"].get<std::vector<int>>();

    stump::GameObject& gird = scene->add_game_object();
    auto&              dirt = gird.add_component<DirtGrid>(engine.get_renderer());
    gird.get_transform().set_parent(level_holder.get_transform());

    for (int i = 0; i < grid_array.size(); ++i)
    {
        if (!grid_array[i])
            continue;

        int x = i % GridSettings::grid_tile_count.x;
        int y = i / static_cast<float>(GridSettings::grid_tile_count.x);
        dirt.delete_on_texture(SDL_Rect{
            GridSettings::grid_offset.x + x * GridSettings::grid_tile_pixel_size.x,
            GridSettings::grid_offset.y + y * GridSettings::grid_tile_pixel_size.y,
            GridSettings::grid_tile_pixel_size.x,
            GridSettings::grid_tile_pixel_size.y });

        auto location = x + y * GridSettings::grid_tile_count.x + 1;
        if (location < grid_array.size() && grid_array[location])
            dirt.clear_wall_between({ x, y }, { x + 1, y });

        location = x + y * GridSettings::grid_tile_count.x - 1;
        if (location > 0 && grid_array[location])
            dirt.clear_wall_between({ x, y }, { x - 1, y });

        location = x + y * GridSettings::grid_tile_count.x + GridSettings::grid_tile_count.x;
        if (location < grid_array.size() && grid_array[location])
            dirt.clear_wall_between({ x, y }, { x, y + 1 });

        location = x + y * GridSettings::grid_tile_count.x - GridSettings::grid_tile_count.x;
        if (location > 0 && grid_array[location])
            dirt.clear_wall_between({ x, y }, { x, y - 1 });
    }

    stump::GameObject& digger = scene->add_game_object();
    digger.add_component<stump::Texture2DSpriteSheet>("data/SpritesPlayers.png").set_sprite_size({ 16, 16 }).set_size_multiplier(3);
    digger.add_component<GridTransform>(glm::ivec2{ level_json["PlayerSpawnLocation1"]["x"].get<int>(), level_json["PlayerSpawnLocation1"]["y"].get<int>() });
    digger.add_component<Digger>();
    digger.add_component<DirtEraser>(dirt);
    digger.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& nobbin = scene->add_game_object();
    auto&              sprite_sheet = nobbin.add_component<stump::Texture2DSpriteSheet>("data/SpritesEnemies.png").set_sprite_size({ 16, 15 }).set_size_multiplier(3);
    auto&              transform = nobbin.add_component<GridTransform>(glm::ivec2{ level_json["EnemySpawnLocation"]["x"].get<int>(), level_json["EnemySpawnLocation"]["y"].get<int>() });
    nobbin.add_component<Nobbin>(transform, dirt, sprite_sheet);
    nobbin.add_component<DirtEraser>(dirt);
    nobbin.get_transform().set_parent(level_holder.get_transform());

    for (auto gold_location : level_json["GoldBags"])
    {
        int x = gold_location["x"].get<int>();
        int y = gold_location["y"].get<int>();

        auto& gold_bag = scene->add_game_object();
        gold_bag.add_component<GoldBag>();
        gold_bag.add_component<stump::Texture2DSpriteSheet>("data/SpritesItems.png").set_sprite_size({ 16, 15 }).set_sprite_index({ 0, 0 }).set_size_multiplier(3);
        gold_bag.add_component<GridTransform>(glm::ivec2{ x, y });
    }

    for (auto gems : level_json["Gems"])
    {
        int x = gems["x"].get<int>();
        int y = gems["y"].get<int>();

        auto& gem = scene->add_game_object();
        gem.add_component<stump::Texture2DSpriteSheet>("data/SpritesItems.png").set_sprite_size({ 16, 15 }).set_sprite_index({ 0, 2 }).set_size_multiplier(3);
        gem.add_component<GridTransform>(glm::ivec2{ x, y });
    }

    return std::move(scene);
}