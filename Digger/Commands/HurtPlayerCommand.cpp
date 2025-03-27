#include "HurtPlayerCommand.h"

HurtPlayerCommand::HurtPlayerCommand(CharacterStats& character): m_character(character)
{
}

void HurtPlayerCommand::execute()
{
    m_character.remove_health();
}
