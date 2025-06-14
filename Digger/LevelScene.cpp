#include "Scenes.h"

#include "Components/ColliderGrid.h"

#include <memory>

#include "Components/CollisionHolder.h"
#include "Components/DirtEraser.h"
#include "Components/DirtGrid.h"
#include "Components/Gem.h"
#include "Components/GoldBag/GoldBag.h"
#include "Components/GridTransform.h"
#include "Components/NobbinSpawner.h"
#include "Components/Nobbin/Nobbin.h"
#include "Components/Nobbin/NobbinAI.h"

#include <GameObject.h>
#include <StumpEngine.h>
#include <fstream>
#include <Component/Texture2DSpriteSheet.h>
#include <nlohmann/json.hpp>

std::unique_ptr<stump::Scene> Scenes::level_scene(stump::StumpEngine& engine, GameModes mode, const std::string& level)
{
    auto scene = std::make_unique<stump::Scene>(engine);

    // Parse file
    std::ifstream  file(level);
    nlohmann::json level_json = nlohmann::json::parse(file);

    // Collision setup
    auto& game_things = scene->add_game_object();
    auto& collider_holder = game_things.add_component<CollisionHolder>();

    // Grid setup
    stump::GameObject& gird = scene->add_game_object();
    auto&              dirt = gird.add_component<DirtGrid>(engine.get_renderer());

    auto& game_data_tracker = game_things.add_component<GameDataTracker>(dirt);

    // Generate grid from level
    std::vector<int> grid_array = level_json["grid"].get<std::vector<int>>();
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

    // Spawn players

    int spawn_count = 1;
    if (mode == GameModes::coop || mode == GameModes::versus)
        spawn_count = 2;

    for (int i = 0; i < spawn_count; ++i)
    {
        stump::GameObject& digger = scene->add_game_object();
        digger.add_component<stump::Texture2DSpriteSheet>("data/SpritesPlayers.png").set_sprite_size({ 16, 16 }).set_size_multiplier(3);

        std::string spawn_string = i == 0 ? "PlayerSpawnLocation1" : "PlayerSpawnLocation2";
        auto&       grid_transform = digger.add_component<GridTransform>(glm::ivec2{ level_json[spawn_string]["x"].get<int>(), level_json[spawn_string]["y"].get<int>() });

        UseInput input{ UseInput::keyboard_and_gamepad };
        if (mode == GameModes::coop || mode == GameModes::versus)
        {
            if (stump::InputManager::instance().get_gamepads().size() >= 2)
            {
                if (i == 0)
                    input = UseInput::gamepad1;
                else
                    input = UseInput::gamepad2;
            }
            else
            {
                if (i == 0)
                    input = UseInput::keyboard;
                else
                    input = UseInput::gamepad1;
            }
        }

        digger.add_component<Digger>(input, i != 0);
        digger.add_component<DirtEraser>(dirt);
        digger.add_component<ColliderGrid>(grid_transform, collider_holder, 0);

        game_data_tracker.add_player(grid_transform);
    }

    auto& spawner_gm = scene->add_game_object();
    spawner_gm.add_component<NobbinSpawner>(*scene.get(),
                                            dirt,
                                            collider_holder,
                                            game_data_tracker,
                                            glm::ivec2{ level_json["EnemySpawnLocation"]["x"].get<int>(), level_json["EnemySpawnLocation"]["y"].get<int>() },
                                            mode,
                                            UseInput::keyboard_and_gamepad);

    // Spawn gold bags
    for (auto gold_location : level_json["GoldBags"])
    {
        int x = gold_location["x"].get<int>();
        int y = gold_location["y"].get<int>();

        auto& gold_bag_gm = scene->add_game_object();
        auto& texture = gold_bag_gm.add_component<stump::Texture2DSpriteSheet>("data/SpritesItems.png").set_sprite_size({ 16, 16 }).set_sprite_index({ 0, 0 }).set_size_multiplier(3);
        auto& bag_transform = gold_bag_gm.add_component<GridTransform>(glm::ivec2{ x, y });
        auto& collider = gold_bag_gm.add_component<ColliderGrid>(bag_transform, collider_holder, 2);
        gold_bag_gm.add_component<DirtEraser>(dirt);
        gold_bag_gm.add_component<GoldBag>(bag_transform, dirt, texture, collider);
    }

    // Spawn gems
    for (auto gems : level_json["Gems"])
    {
        int x = gems["x"].get<int>();
        int y = gems["y"].get<int>();

        auto& gem = scene->add_game_object();
        gem.add_component<stump::Texture2DSpriteSheet>("data/SpritesItems.png").set_sprite_size({ 16, 16 }).set_sprite_index({ 0, 2 }).set_size_multiplier(3);
        auto& gem_transform = gem.add_component<GridTransform>(glm::ivec2{ x, y });
        auto& collider = gem.add_component<ColliderGrid>(gem_transform, collider_holder, 3);
        gem.add_component<Gem>(collider);
    }

    return std::move(scene);
}