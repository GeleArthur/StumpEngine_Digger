#pragma once
#include <Command.h>

#include "../Components/Digger.h"

class DiggerHorizontalCommand final : public stump::Command
{
public:
    explicit DiggerHorizontalCommand(Digger& digger, bool left);
    void execute() override;

private:
    Digger& m_digger;
    float   m_current_time{};
    bool    m_move;
};

class DiggerVerticalCommand final : public stump::Command
{
public:
    explicit DiggerVerticalCommand(Digger& digger, bool down);
    void execute() override;

private:
    Digger& m_digger;
    float   m_current_time{};
    bool    m_move;
};
