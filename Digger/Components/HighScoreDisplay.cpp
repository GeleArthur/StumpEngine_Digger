#include "HighScoreDisplay.h"

#include <Scene.h>
#include <fstream>
#include <Component/TextDisplay.h>
HighScoreDisplay::HighScoreDisplay(stump::GameObject& attached, stump::Scene& scene)
    : Component{ attached }
{
    std::ifstream score_json = std::ifstream("highscore.json");
    if (!score_json.is_open())
    {
        auto& no_score_gm = scene.add_game_object();
        // no_score_gm.get_transform().set_local_position({ 0, 0 });
        no_score_gm.get_transform().set_parent(attached.get_transform());
        no_score_gm.add_component<stump::TextDisplay>("data/DiggerFont.ttf", "... ???", 32.0f, SDL_Color{ 204, 116, 0 });

        return;
    }
}