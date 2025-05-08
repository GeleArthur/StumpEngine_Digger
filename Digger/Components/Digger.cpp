#include "Digger.h"

#include <GameObject.h>
#include <StumpEngine.h>

#include "../Commands/DiggerMoveCommand.h"

Digger::Digger(GameObject& attached): Component{attached}
{
    get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_D, input_pressed_type::held_down, std::make_unique<DiggerMoveCommand>(*this));
}
