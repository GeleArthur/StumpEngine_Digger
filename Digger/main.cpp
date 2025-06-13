#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <StumpEngine.h>
#include <SoundSystem/SoundSystemLocator.h>
#include <SoundSystem/SoundSystemLogger.h>
#include <SoundSystem/SoundSystemSDL3_Mixer.h>

#include "Scenes.h"
#include <nlohmann/json.hpp>

#if defined(WIN32)
#include <windows.h>
#endif

void AllocateConsole()
{
#if defined(WIN32)
    if (AllocConsole()) // Allocate a new console for the application
    {
        FILE* fp; // Redirect STDOUT to the console
        freopen_s(&fp, "CONOUT$", "w", stdout);
        setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering for stdout

        freopen_s(&fp, "CONOUT$", "w", stderr); // Redirect STDERR to the console
        setvbuf(stderr, NULL, _IONBF, 0);       // Disable buffering for stderr

        freopen_s(&fp, "CONIN$", "r", stdin); // Redirect STDIN to the console
        setvbuf(stdin, NULL, _IONBF, 0);      // Disable buffering for stdin

        std::ios::sync_with_stdio(true); // Sync C++ streams with the console
    }
#endif
}

static void init_game(stump::StumpEngine& engine)
{
    engine.set_window_size(900, 600);
    stump::SoundSystemLocator::register_sound_system(std::make_unique<stump::SoundSystemLogger>(std::make_unique<stump::SoundSystemSDL3_Mixer>()));

    engine.set_active_scene(Scenes::level_scene(engine));
    // engine.set_active_scene(Scenes::level_scene(engine));
    engine.set_active_scene(Scenes::ui_scene(engine));
}

int main(int, char*[])
{
    AllocateConsole();

    stump::StumpEngine{ init_game }.run();

    return 0;
}
