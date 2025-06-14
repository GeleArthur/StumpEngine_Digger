#include "Scenes.h"
#include "Components/HighScoreDisplay.h"
#include "Components/ModeSelectUI.h"

#include <Scene.h>
#include <Component/TextDisplay.h>
#include <Component/Texture2D.h>

void quick_text(stump::Scene& scene, glm::vec2 pos, const std::string& text, SDL_Color color)
{
    stump::GameObject& highscore = scene.add_game_object();
    highscore.get_transform().set_local_position(pos);
    highscore.add_component<stump::TextDisplay>("data/DiggerFont.ttf", text, 32.0f, color);
}

std::unique_ptr<stump::Scene> Scenes::ui_scene(stump::StumpEngine& engine)
{
    auto scene = std::make_unique<stump::Scene>(engine);

    stump::GameObject& background = scene->add_game_object();
    background.add_component<stump::Texture2D>("data/uibackground.png");

    quick_text(*scene.get(), { 550, 200 }, "One Player", { 204, 116, 0 });
    quick_text(*scene.get(), { 550, 300 }, "Co-op mode", { 204, 116, 0 });
    quick_text(*scene.get(), { 550, 400 }, "Versus mode", { 204, 116, 0 });

    quick_text(*scene.get(), { 100, 100 }, "High Score", { 204, 116, 0 });

    auto& high_score = scene->add_game_object();
    high_score.get_transform().set_local_position({ 100, 200 });
    high_score.add_component<HighScoreDisplay>(*scene.get());

    auto& mode_select_ui = scene->add_game_object();
    mode_select_ui.add_component<ModeSelectUi>(*scene.get());

    // stump::GameObject& highscore = scene->add_game_object();
    // highscore.get_transform().set_local_position({ 600, 100 });
    // highscore.add_component<stump::TextDisplay>("data/DiggerFont.ttf", "One Player", 32.0f, SDL_Color{ 204, 116, 0 });

    // stump::GameObject& highscore = scene->add_game_object();
    // highscore.get_transform().set_local_position({ 600, 100 });
    // highscore.add_component<stump::TextDisplay>("data/DiggerFont.ttf", "One Player", 32.0f, SDL_Color{ 204, 116, 0 });

    return std::move(scene);
}