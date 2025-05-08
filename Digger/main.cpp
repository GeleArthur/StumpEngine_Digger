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

#include "GameObject.h"
#include "Component/TextDisplay.h"
#include "Component/Texture2D.h"
#include "Component/Transform.h"
#include "Components/BackGroundDrawer.h"
#include "../StumpEngine/Component/FpsShowCase.h"
#include "Components/Digger.h"


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
        setvbuf(stderr, NULL, _IONBF, 0); // Disable buffering for stderr

        freopen_s(&fp, "CONIN$", "r", stdin); // Redirect STDIN to the console
        setvbuf(stdin, NULL, _IONBF, 0); // Disable buffering for stdin

        std::ios::sync_with_stdio(true); // Sync C++ streams with the console
    }
#endif
}


static void init_game(StumpEngine& engine)
{
    GameObject& back_ground = engine.add_game_object();
    back_ground.get_transform().set_local_position(glm::vec2{0.0f, 0.0f});
    back_ground.add_component<Texture2D>("data/background.tga");

    GameObject& background = engine.add_game_object();
    BackGroundDrawer& back_ground_drawer = background.add_component<BackGroundDrawer>();

    GameObject& fps_display = engine.add_game_object();
    fps_display.get_transform().set_local_position(glm::vec2{0, 0});
    fps_display.add_component<TextDisplay>("data/Lingua.otf", "", 10.0f);
    fps_display.add_component<FpsShowcase>();

    GameObject& digger = engine.add_game_object();
    digger.add_component<Texture2D>("data/driller.png");
    digger.add_component<Digger>();


    // engine.get_input().bind_keyboard(
    //     SDL_SCANCODE_C,
    //     input_pressed_type::pressed_this_frame,
    //     std::make_unique<HurtPlayerCommand>(stats));
    //
    // engine.get_input().bind_keyboard(
    //     SDL_SCANCODE_Z,
    //     input_pressed_type::pressed_this_frame,
    //     std::make_unique<AddScorePlayerCommand>(stats, 10));
    //
    // engine.get_input().bind_keyboard(
    //     SDL_SCANCODE_X,
    //     input_pressed_type::pressed_this_frame,
    //     std::make_unique<AddScorePlayerCommand>(stats, 100));
    //
    // engine.get_input().bind_gamepad_button(
    //     SDL_GAMEPAD_BUTTON_WEST,
    //     input_pressed_type::pressed_this_frame,
    //     std::make_unique<HurtPlayerCommand>(stats2));
    //
    // engine.get_input().bind_gamepad_button(
    //     SDL_GAMEPAD_BUTTON_EAST,
    //     input_pressed_type::pressed_this_frame,
    //     std::make_unique<AddScorePlayerCommand>(stats2, 10));
    //
    // engine.get_input().bind_gamepad_button(
    //     SDL_GAMEPAD_BUTTON_SOUTH,
    //     input_pressed_type::pressed_this_frame,
    //     std::make_unique<AddScorePlayerCommand>(stats2, 100));


    SoundSystemLocator::register_sound_system(std::make_unique<SoundSystemLogger>(std::make_unique<SoundSystemSDL3_Mixer>()));
}

int main(int, char*[])
{
    AllocateConsole();
    auto engine = StumpEngine{init_game};
    engine.run();

    return 0;
}

