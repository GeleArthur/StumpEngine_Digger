#include "AddScorePlayerCommand.h"

AddScorePlayerCommand::AddScorePlayerCommand(CharacterStats& character, const int amount):
    m_character(character),
    m_amount{amount}
{
}

void AddScorePlayerCommand::execute()
{
    m_character.add_score(m_amount);
}
