#pragma once
#include <Command.h>

#include "../Components/Digger.h"

class DiggerMoveCommand final : public Command
{
public:
    explicit DiggerMoveCommand(Digger& digger);
    void execute() override;

private:
    Digger& m_digger;
    float m_current_time{};
};
