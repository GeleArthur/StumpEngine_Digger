#pragma once
#include <format>
#include <isteamuserstats.h>

#include "CharacterStats.h"
#include "Component.h"
#include "TextDisplay.h"
#include "../EventListener.h"
#include "../GameObject.h"

class CharacterStats;

class CharacterStatsDisplay final : public Component, public EventListener
{
public:
    CharacterStatsDisplay(GameObject& game_object, CharacterStats& health):
        Component{game_object},
        m_character(health),
        m_text_display{*game_object.get_component<TextDisplay>()}
    {
    }

    void on_health_changed(int health)
    {
        m_text_display.update_text(std::format("#lives {}", health));

        if (health < 0)
        {
            SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
            // SteamUserStats()->ClearAchievement("ACH_WIN_ONE_GAME");
        }
    }

private:
    CharacterStats& m_character;
    TextDisplay& m_text_display;
};



