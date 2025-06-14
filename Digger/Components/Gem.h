#pragma once
#include <EventListener.h>
#include <vec2.hpp>
#include <Component/Component.h>

class ColliderGrid;
class Gem final : public stump::Component
{
public:
    explicit Gem(stump::GameObject& attached_game_object, ColliderGrid& collider);
    void collided(const ColliderGrid& tag, glm::ivec2 direction) const;

private:
    stump::EventListener<ColliderGrid&, glm::ivec2> m_collided{ [this](ColliderGrid& tag, glm::ivec2 direction) { collided(tag, direction); } };
};
