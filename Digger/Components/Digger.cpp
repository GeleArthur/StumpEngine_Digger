#include "Digger.h"

#include <GameObject.h>
#include <StumpEngine.h>

#include "../Commands/DiggerMoveCommand.h"

Digger::Digger(stump::GameObject& attached, GridTransform& gold_bag)
    : Component{ attached }
    , gold_bag{ gold_bag }
{
    // I don't get the command pattern this kinda sucks
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_D, stump::input_pressed_type::held_down, std::make_unique<DiggerHorizontalCommand>(*this, true));
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_A, stump::input_pressed_type::held_down, std::make_unique<DiggerHorizontalCommand>(*this, false));
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_W, stump::input_pressed_type::held_down, std::make_unique<DiggerVerticalCommand>(*this, false));
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_S, stump::input_pressed_type::held_down, std::make_unique<DiggerVerticalCommand>(*this, true));
}
void Digger::update()
{
}
