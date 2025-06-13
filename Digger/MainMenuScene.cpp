#include "Scenes.h"

#include <Scene.h>
#include <Component/TextDisplay.h>

std::unique_ptr<stump::Scene> Scenes::ui_scene(stump::StumpEngine& engine)
{
    auto scene = std::make_unique<stump::Scene>(engine);

    stump::GameObject& highscore = scene->add_game_object();
    highscore.get_transform().set_local_position({ 0, 0 });
    highscore.add_component<stump::TextDisplay>("data/DiggerFont.ttf", "One Player", 32.0f);

    return std::move(scene);
}