#if _DEBUG
 // ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "GameObject.h"
#include "Minigin.h"

static void init_game(Minigin& engine)
{
	GameObject* coolObject = engine.add_game_object();
    coolObject->add_component<Component>();

    // auto yea = std::type_index<typeid(int)>;
}


// What do you think of this? I am avoiding globals with the appstate
// But the new and delete are not great. Or could you maybe say its allow for this instance.
// I also would assume that when I make my game. There is only 1 start up function that gets called by the engine.
// The game can then spawn game_objects to continue the game.

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