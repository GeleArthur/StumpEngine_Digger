//
// Created by a on 16/03/2025.
//

#include "HurtPlayerCommand.h"

HurtPlayerCommand::HurtPlayerCommand(CharacterStats& character): m_character(character)
{
}

void HurtPlayerCommand::execute()
{
    m_character.remove_health();
}
