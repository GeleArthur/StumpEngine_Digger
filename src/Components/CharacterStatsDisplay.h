#pragma once
#include <format>
#include <isteamuserstats.h>

#include "CharacterStats.h"
#include "Component.h"
#include "TextDisplay.h"
#include "../EventListener.h"
#include "../GameObject.h"

class CharacterStats;

class CharacterStatsDisplay final : public Component
{
public:
    CharacterStatsDisplay(const CharacterStatsDisplay& other) = delete;
    CharacterStatsDisplay(CharacterStatsDisplay&& other) = delete;
    CharacterStatsDisplay& operator=(const CharacterStatsDisplay& other) = delete;
    CharacterStatsDisplay& operator=(CharacterStatsDisplay&& other) = delete;

    CharacterStatsDisplay(GameObject& game_object, CharacterStats& health):
        Component{game_object},
        m_character(health),
        m_text_display{*game_object.get_component<TextDisplay>()},
        m_listener_health_changed(std::bind(&CharacterStatsDisplay::on_health_changed, this, std::placeholders::_1))
    {
        health.on_health_changed.add_listener(&m_listener_health_changed);
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
    EventListener<int> m_listener_health_changed;
    CharacterStats& m_character;
    TextDisplay& m_text_display;
};



