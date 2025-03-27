#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <steam_api.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


#include "GameObject.h"
#include "Minigin.h"
#include "Commands/AddScorePlayerCommand.h"
#include "Commands/HurtPlayerCommand.h"
#include "Component/TextDisplay.h"
#include "Component/Texture2D.h"
#include "Component/Transform.h"
#include "Components/CharacterMovement.h"
#include "Components/CharacterStats.h"
#include "Components/CharacterStatsDisplay.h"
#include "Components/FpsShowCase.h"
#include "Components/ImguiTashTheCache.h"


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


static void init_game(Minigin& engine)
{
    GameObject& back_ground = engine.add_game_object();
    back_ground.get_transform().set_local_position(glm::vec2{0.0f, 0.0f});
    back_ground.add_component<Texture2D>("data/background.tga");


    GameObject& logo = engine.add_game_object();
    logo.get_transform().set_local_position(glm::vec2{200.0f, 225.0f});
    logo.add_component<Texture2D>("data/logo.tga");

    GameObject& fps_display = engine.add_game_object();
    fps_display.get_transform().set_local_position(glm::vec2{0, 0});
    fps_display.add_component<TextDisplay>("data/Lingua.otf", "", 30.0f);
    fps_display.add_component<FpsShowcase>();

    GameObject& text_display = engine.add_game_object();
    text_display.get_transform().set_local_position(glm::vec2{200, 0});
    text_display.add_component<TextDisplay>("data/Lingua.otf", "Programming 4 Assignment", 30.0f);

    GameObject& center = engine.add_game_object();
    center.get_transform().set_local_position({200, 200});


    GameObject& character1 = engine.add_game_object();
    character1.get_transform().set_local_position({100, 100});
    character1.add_component<Texture2D>("data/driller.png");
    character1.add_component<CharacterMovement>(true);
    CharacterStats& stats = character1.add_component<CharacterStats>();

    GameObject& text_display1 = engine.add_game_object();
    text_display1.get_transform().set_local_position({0, 200});
    text_display1.add_component<TextDisplay>("data/Lingua.otf", "#lives 3\nscore: 0", 16.0f);
    text_display1.add_component<CharacterStatsDisplay>(stats);

    GameObject& character2 = engine.add_game_object();
    character2.get_transform().set_local_position({100, 200});
    character2.add_component<Texture2D>("data/scary.png");
    character2.add_component<CharacterMovement>(false);
    CharacterStats& stats2 = character2.add_component<CharacterStats>();

    GameObject& text_display2 = engine.add_game_object();
    text_display2.get_transform().set_local_position({0, 250});
    text_display2.add_component<TextDisplay>("data/Lingua.otf", "#lives 3\nscore: 0", 16.0f);
    text_display2.add_component<CharacterStatsDisplay>(stats2);

    GameObject& text_display_info = engine.add_game_object();
    text_display_info.get_transform().set_local_position({5, 50});
    text_display_info.add_component<TextDisplay>("data/Lingua.otf", "Use the D-Pad to move Driller, X to inflict damage, A and B to add score");

    GameObject& text_display_info2 = engine.add_game_object();
    text_display_info2.get_transform().set_local_position({5, 70});
    text_display_info2.add_component<TextDisplay>("data/Lingua.otf", "Use WASD to move enemy, C to inflict damage, Z and X to add score");


    engine.get_input().bind_keyboard(
        SDL_SCANCODE_C,
        input_pressed_type::pressed_this_frame,
        std::make_unique<HurtPlayerCommand>(stats));

    engine.get_input().bind_keyboard(
        SDL_SCANCODE_Z,
        input_pressed_type::pressed_this_frame,
        std::make_unique<AddScorePlayerCommand>(stats, 10));

    engine.get_input().bind_keyboard(
        SDL_SCANCODE_X,
        input_pressed_type::pressed_this_frame,
        std::make_unique<AddScorePlayerCommand>(stats, 100));

    engine.get_input().bind_gamepad_button(
        SDL_GAMEPAD_BUTTON_WEST,
        input_pressed_type::pressed_this_frame,
        std::make_unique<HurtPlayerCommand>(stats2));

    engine.get_input().bind_gamepad_button(
        SDL_GAMEPAD_BUTTON_EAST,
        input_pressed_type::pressed_this_frame,
        std::make_unique<AddScorePlayerCommand>(stats2, 10));

    engine.get_input().bind_gamepad_button(
        SDL_GAMEPAD_BUTTON_SOUTH,
        input_pressed_type::pressed_this_frame,
        std::make_unique<AddScorePlayerCommand>(stats2, 100));


    // stats.on_health_changed.add_listener(&display, &CharacterStatsDisplay::on_health_changed);


    //GameObject& imgui_stuff = engine.add_game_object();
    //imgui_stuff.add_component<ImguiTashTheCache>();

    // class FACK : public Component, public EventListener
    // {
    // public:
    //     FACK(GameObject& fack) : Component{fack}
    //     {
    //         // damm.add_listener(this, &FACK::callmebaby);
    //         damm.notify_listeners(3, 5);
    //     }
    //
    // private:
    //     void callmebaby(int input, int)
    //     {
    //         std::cout << input;
    //     }
    //
    //     Event<int, int> damm;
    // };

    // text_display.add_component<FACK>();
}

int main(int, char*[])
{
    AllocateConsole();
    auto engine = Minigin{init_game};
    engine.run();

    return 0;
}

