#if _DEBUG
 // ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Minigin.h"


SDL_AppResult SDL_AppInit(void** appstate, int , char *[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    auto engine = new Minigin{};
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