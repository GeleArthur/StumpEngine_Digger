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
#include "orbit_around.h"
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
    logo.add_component<OrbitAround>(30.0f, 0.7f);

    GameObject& fps_display = engine.add_game_object();
    fps_display.add_component<Transform>(glm::vec2{0, 0});
    fps_display.add_component<TextDisplay>("data/Lingua.otf", "", 30.0f);
    fps_display.add_component<FpsShowcase>();

    GameObject& text_display = engine.add_game_object();
    text_display.add_component<Transform>(glm::vec2{200, 0});
    text_display.add_component<TextDisplay>("data/Lingua.otf", "Programming 4 Assignment", 30.0f);


    GameObject& logo2 = engine.add_game_object();
    auto& transform_logo = logo2.add_component<Transform>(glm::vec2{0.0f, 0.0f});

    transform_logo.set_parent(*logo.get_component<Transform>());
    logo2.add_component<Texture2D>("data/logo.tga");
    logo2.add_component<OrbitAround>(50.0f, 1.2f);
}

int SDL_main(int, char*[])
{
    auto engine = Minigin{init_game};

    engine.run();

    return 0;
}

