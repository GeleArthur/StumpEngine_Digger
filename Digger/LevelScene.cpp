#include "LevelScene.h"
#include <memory>

#include "Components/DirtEraser.h"
#include "Components/DirtGrid.h"
#include "Components/GridTransform.h"
#include "Components/Nobbin/Nobbin.h"

#include <GameObject.h>
#include <StumpEngine.h>
#include <Component/FpsShowCase.h>
#include <Component/TextDisplay.h>
#include <Component/Texture2DSpriteSheet.h>

std::unique_ptr<stump::Scene> Scenes::level_scene(stump::StumpEngine& engine)
{
    auto scene = std::make_unique<stump::Scene>(engine);

    auto& level_holder = scene->add_game_object();

    stump::GameObject& gird = scene->add_game_object();
    auto&              dirt = gird.add_component<DirtGrid>(engine.get_renderer());
    gird.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& digger = scene->add_game_object();
    digger.add_component<stump::Texture2DSpriteSheet>("data/SpritesPlayers.png").set_sprite_size({ 16, 16 }).set_size_multiplier(3);
    digger.add_component<GridTransform>();
    digger.add_component<Digger>();
    digger.add_component<DirtEraser>(dirt);
    digger.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& nobbin = scene->add_game_object();
    auto&              sprite_sheet = nobbin.add_component<stump::Texture2DSpriteSheet>("data/SpritesEnemies.png").set_sprite_size({ 16, 15 }).set_size_multiplier(3);
    auto&              transform = nobbin.add_component<GridTransform>();
    nobbin.add_component<Nobbin>(transform, dirt, sprite_sheet);
    nobbin.add_component<DirtEraser>(dirt);
    nobbin.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& fps_display = scene->add_game_object();
    fps_display.get_transform().set_local_position(glm::vec2{ 0, 0 });
    fps_display.add_component<stump::TextDisplay>("data/Lingua.otf", "", 10.0f);
    fps_display.add_component<stump::FpsShowcase>();

    fps_display.get_transform().set_parent(level_holder.get_transform());

    return std::move(scene);
}