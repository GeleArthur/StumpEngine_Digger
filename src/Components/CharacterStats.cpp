#include "CharacterStats.h"
#include "../GameObject.h"

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

void CharacterStats::add_score(const int amount)
{
    m_score += amount;
    on_score_changed.notify_listeners(m_score);
}
