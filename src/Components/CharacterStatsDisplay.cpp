//
// Created by a on 16/03/2025.
//

#include "CharacterStatsDisplay.h"

CharacterStatsDisplay::CharacterStatsDisplay(GameObject& game_object, CharacterStats& health):
    Component{game_object},
    m_health{health.get_health()},
    m_score{health.get_score()},
    m_listener_health_changed(std::bind(&CharacterStatsDisplay::on_health_changed, this, std::placeholders::_1)),
    m_listener_score_changed(std::bind(&CharacterStatsDisplay::on_score_changed, this, std::placeholders::_1)),
    m_character(health),
    m_text_display{*game_object.get_component<TextDisplay>()}
{
    health.on_health_changed.add_listener(&m_listener_health_changed);
    health.on_score_changed.add_listener(&m_listener_score_changed);
    update_text();
}

void CharacterStatsDisplay::on_health_changed(int health)
{
    m_health = health;
    update_text();
}

void CharacterStatsDisplay::on_score_changed(int score)
{
    m_score = score;
    update_text();
}

void CharacterStatsDisplay::update_text()
{
    m_text_display.update_text(std::format("#lives {}\nscore {}", m_health, m_score));
}
