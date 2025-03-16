#pragma once
#include <format>
#include "CharacterHealth.h"
#include "Component.h"
#include "TextDisplay.h"
#include "../GameObject.h"

class CharacterHealth;

class CharacterStatsDisplay : public Component, EventListener<int>
{
public:
    CharacterStatsDisplay(GameObject& game_object, CharacterHealth& health):
        Component{game_object},
        m_character(health),
        m_text_display{*game_object.get_component<TextDisplay>()}
    {
        m_character.on_health_changed.add_listener(this);
    }

    virtual void notify(int health) override
    {
        m_text_display.update_text(std::format("#lives {}", health));
    }

private:
    CharacterHealth& m_character;
    TextDisplay& m_text_display;
};



