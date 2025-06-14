#include "GetHit.h"
GetHit::GetHit(stump::GameObject& attached, ColliderGrid& collider, const Team team)
    : Component{ attached }
    , m_collider{ &collider }
    , m_team{ team }
    , m_collided{ [this](const uint64_t tag, const glm::ivec2 dir) { collided(tag, dir); } }
{
}

void GetHit::collided(uint64_t tag, glm::ivec2 direction)
{
    if (m_team == Team::digger)
    {
        if (tag == 2) // Gold bags // Should use string hash but time
        {
            m_death.notify_listeners();
        }
        if (tag == 1)
        {
            m_death.notify_listeners();
        }
    }
    else
    {
        if (tag == 2) // Gold bags // Should use string hash but time
        {
            m_death.notify_listeners();
        }
    }
}
