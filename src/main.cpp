#if _DEBUG
 // ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#define SDL_MAIN_USE_CALLBACKS
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
	GameObject* back_ground = engine.add_game_object();
    back_ground->add_component<Transform>(glm::vec2{ 0.0f, 0.0f });
    back_ground->add_component<Texture2D>("data/background.tga");

    GameObject* logo = engine.add_game_object();
    logo->add_component<Transform>(glm::vec2{ 200.0f, 225.0f });
    logo->add_component<Texture2D>("data/logo.tga");

    GameObject* fps_display = engine.add_game_object();
    fps_display->add_component<Transform>(glm::vec2{ 0, 0 });
    fps_display->add_component<TextDisplay>("data/Lingua.otf", "", 30.0f);
    fps_display->add_component<FpsShowcase>();

    GameObject* text_display = engine.add_game_object();
    text_display->add_component<Transform>(glm::vec2{ 200, 0 });
    text_display->add_component<TextDisplay>("data/Lingua.otf", "Programming 4 Assignment", 30.0f);

}


// What do you think of this? I am avoiding globals with the appstate
// But the new and delete are not great. Or could you maybe say its allow for this instance.
// I also would assume that when I make my game. There is only 1 start up function that gets called by the engine.
// The game can then spawn game_objects to continue the game.

// Maybe just have 1 main function and that handle emscripten my self.

SDL_AppResult SDL_AppInit(void** appstate, int , char *[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    auto engine = new Minigin{&init_game };
    *appstate = reinterpret_cast<void*>(engine);

    return SDL_APP_CONTINUE;  
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event *event)
{
    static_cast<Minigin*>(appstate)->event(event);
    return SDL_APP_CONTINUE;  
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    return static_cast<Minigin*>(appstate)->iterate();
}

void SDL_AppQuit(void* appstate, SDL_AppResult )
{
    delete static_cast<Minigin*>(appstate);
}