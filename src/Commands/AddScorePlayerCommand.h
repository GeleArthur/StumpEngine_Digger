#pragma once
#include "Command.h"
#include "../Components/CharacterStats.h"


class AddScorePlayerCommand : public Command
{
public:
    explicit AddScorePlayerCommand(CharacterStats& character, int amount);

    void execute() override;

private:
    CharacterStats& m_character;
    int m_amount{};
};
