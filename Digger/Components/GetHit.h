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

    void collided(uint64_t, glm::ivec2);
    
private:
    Team           m_team;
    ColliderGrid*  m_collider;
    stump::Event<> m_death;
    stump::Event<> m_death_animation;

    stump::EventListener<uint64_t, glm::ivec2> m_collided;
};
