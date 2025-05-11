#include "Digger.h"

#include <GameObject.h>
#include <StumpEngine.h>

#include "../Commands/DiggerMoveCommand.h"

Digger::Digger(GameObject& attached)
    : Component{ attached }
{
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_D, input_pressed_type::held_down, std::make_unique<DiggerHorizontalCommand>(*this, true));
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_A, input_pressed_type::held_down, std::make_unique<DiggerHorizontalCommand>(*this, false));
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_W, input_pressed_type::held_down, std::make_unique<DiggerVerticalCommand>(*this, false));
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_S, input_pressed_type::held_down, std::make_unique<DiggerVerticalCommand>(*this, true));
}
void Digger::update()
{
}
