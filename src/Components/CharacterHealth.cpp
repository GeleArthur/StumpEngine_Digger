//
// Created by a on 13/03/2025.
//

#include "CharacterHealth.h"

#include "../GameObject.h"
#include "../Minigin.h"

CharacterHealth::CharacterHealth(GameObject& game_object): Component{game_object}
{
    //    game_object.get_engine().get_input().bind_keyboard()
}
