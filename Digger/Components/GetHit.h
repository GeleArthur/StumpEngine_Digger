#pragma once
#include "ColliderGrid.h"
#include "GridTransform.h"

#include <Component/Component.h>

enum class Team
{
    digger,
    nobbin
};

class GetHit final : public stump::Component
{
public:
    explicit GetHit(stump::GameObject& attached, ColliderGrid& collider, Team team);

    void die();

    stump::Event<>& get_death_event()
    {
        return m_death;
    }

private:
    Team           m_team;
    ColliderGrid*  m_collider;
    stump::Event<> m_death;
};
