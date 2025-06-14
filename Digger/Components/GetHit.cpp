#include "GetHit.h"
GetHit::GetHit(stump::GameObject& attached, ColliderGrid& collider, const Team team)
    : Component{ attached }
    , m_collider{ &collider }
    , m_team{ team }
{
}

void GetHit::die()
{
    m_death.notify_listeners();
}
