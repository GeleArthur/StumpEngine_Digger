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
#include "Components/Digger.h"
#include "Components/DirtEraser.h"
#include "Components/DirtGrid.h"
#include "Components/GoldBag.h"
#include "Components/GridTransform.h"
#include "Components/Nobbin/Nobbin.h"

#include <Component/FpsShowCase.h>
#include <Component/Texture2DSpriteSheet.h>

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

    auto& level_holder = engine.add_game_object();

    stump::GameObject& gird = engine.add_game_object();
    auto&              dirt = gird.add_component<DirtGrid>(engine.get_renderer());
    gird.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& digger = engine.add_game_object();
    digger.add_component<stump::Texture2DSpriteSheet>("data/SpritesPlayers.png").set_sprite_size({ 16, 16 }).set_size_multiplier(3);
    digger.add_component<GridTransform>();
    digger.add_component<Digger>();
    digger.add_component<DirtEraser>(dirt);
    digger.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& nobbin = engine.add_game_object();
    auto&              sprite_sheet = nobbin.add_component<stump::Texture2DSpriteSheet>("data/SpritesEnemies.png").set_sprite_size({ 16, 15 }).set_size_multiplier(3);
    auto&              transform = nobbin.add_component<GridTransform>();
    nobbin.add_component<Nobbin>(transform, dirt, sprite_sheet);
    nobbin.add_component<DirtEraser>(dirt);
    nobbin.get_transform().set_parent(level_holder.get_transform());

    stump::GameObject& fps_display = engine.add_game_object();
    fps_display.get_transform().set_local_position(glm::vec2{ 0, 0 });
    fps_display.add_component<stump::TextDisplay>("data/Lingua.otf", "", 10.0f);
    fps_display.add_component<stump::FpsShowcase>();

    fps_display.get_transform().set_parent(level_holder.get_transform());

    level_holder.mark_for_deletion();

    stump::SoundSystemLocator::register_sound_system(std::make_unique<stump::SoundSystemLogger>(std::make_unique<stump::SoundSystemSDL3_Mixer>()));
}

int main(int, char*[])
{
    AllocateConsole();
    stump::StumpEngine{ init_game }.run();

    return 0;
}
