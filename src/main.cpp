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
#include "ImguiTashTheCache.h"
#include "Minigin.h"
#include "OrbitAround.h"
#include "TextDisplay.h"
#include "Texture2D.h"
#include "Transform.h"

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

class SuperCoolTest final : public Command
{
public:
    virtual void execute() override
    {
        std::cout << "YOU PRESSED W";
    };
};

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
    character1.get_transform().set_parent(center.get_transform(), false);
    character1.add_component<Texture2D>("data/driller.png");
    character1.add_component<OrbitAround>(50.0f, 3.2f);

    GameObject& character2 = engine.add_game_object();
    character2.get_transform().set_local_position({100, 100});
    character2.get_transform().set_parent(character1.get_transform(), false);
    character2.add_component<Texture2D>("data/scary.png");
    character2.add_component<OrbitAround>(80.0f, 4.2f);

    engine.get_input().bind_keyboard(
        {SDL_SCANCODE_W, input_pressed_type::let_go_this_frame, false},
        std::make_unique<SuperCoolTest>());

    //GameObject& imgui_stuff = engine.add_game_object();
    //imgui_stuff.add_component<ImguiTashTheCache>();
}

int main(int, char*[])
{
    AllocateConsole();
    auto engine = Minigin{init_game};
    engine.run();

    return 0;
}

