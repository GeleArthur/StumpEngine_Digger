#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "FpsShowCase.h"
#include "GameObject.h"
#include "Minigin.h"
#include "TextDisplay.h"
#include "Texture2D.h"
#include "Transform.h"


static void init_game(Minigin& engine)
{
    GameObject& back_ground = engine.add_game_object();
    back_ground.add_component<Transform>(glm::vec2{0.0f, 0.0f});
    back_ground.add_component<Texture2D>("data/background.tga");

    GameObject& logo = engine.add_game_object();
    logo.add_component<Transform>(glm::vec2{200.0f, 225.0f});
    logo.add_component<Texture2D>("data/logo.tga");

    GameObject& fps_display = engine.add_game_object();
    fps_display.add_component<Transform>(glm::vec2{0, 0});
    fps_display.add_component<TextDisplay>("data/Lingua.otf", "", 30.0f);
    fps_display.add_component<FpsShowcase>();

    GameObject& text_display = engine.add_game_object();
    text_display.add_component<Transform>(glm::vec2{200, 0});
    text_display.add_component<TextDisplay>("data/Lingua.otf", "Programming 4 Assignment", 30.0f);
}

int SDL_main(int, char*[])
{
    auto engine = Minigin{init_game};

    engine.run();

    return 0;
}

