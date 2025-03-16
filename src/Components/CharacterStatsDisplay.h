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
    CharacterStatsDisplay(GameObject& game_object, CharacterStats& health);

    ~CharacterStatsDisplay() override = default;
    CharacterStatsDisplay(const CharacterStatsDisplay& other) = delete;
    CharacterStatsDisplay(CharacterStatsDisplay&& other) = delete;
    CharacterStatsDisplay& operator=(const CharacterStatsDisplay& other) = delete;
    CharacterStatsDisplay& operator=(CharacterStatsDisplay&& other) = delete;

private:
    void on_health_changed(int health);
    void on_score_changed(int score);
    void update_text();
    int m_health;
    int m_score;

    EventListener<int> m_listener_health_changed;
    EventListener<int> m_listener_score_changed;
    CharacterStats& m_character;
    TextDisplay& m_text_display;
};



