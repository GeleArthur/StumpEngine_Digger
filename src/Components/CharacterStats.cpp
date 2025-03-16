//
// Created by a on 13/03/2025.
//

#include "CharacterStats.h"

#include "../GameObject.h"
#include "../Minigin.h"

class HurtPlayerCommand : public Command
{
public:
    explicit HurtPlayerCommand(CharacterStats& character): m_character(character)
    {
    }

    void execute() override
    {
        m_character.remove_health();
    }

private:
    CharacterStats& m_character;
};

class AddScorePlayerCommand : public Command
{
public:
    explicit AddScorePlayerCommand(CharacterStats& character, const int amount):
        m_character(character), m_amount{amount}
    {
    }

    void execute() override
    {
        m_character.add_score(m_amount);
    }

private:
    CharacterStats& m_character;
    int m_amount{};
};

CharacterStats::CharacterStats(GameObject& game_object):
    Component{game_object},
    m_health{3},
    m_score{0}
{
}

void CharacterStats::remove_health()
{
    --m_health;
    on_health_changed.notify_listeners(m_health);
}

void CharacterStats::add_score(int amount)
{
    m_score -= amount;
    on_score_changed.notify_listeners(m_score);
}
