#pragma once
#include "Command.h"
#include "../Components/CharacterStats.h"

class HurtPlayerCommand final : public Command
{
public:
    explicit HurtPlayerCommand(CharacterStats& character);
    void execute() override;

private:
    CharacterStats& m_character;
};
