#pragma once
#include <Event.h>
#include <EventListener.h>
#include <vec2.hpp>
#include <Component/Component.h>

class GameDataTracker;
class ColliderGrid;
class Gem final : public stump::Component
{
public:
    explicit Gem(stump::GameObject& attached_game_object, ColliderGrid& collider, GameDataTracker& tacker);
    void collided(const ColliderGrid& tag, glm::ivec2 direction);

private:
    stump::EventListener<ColliderGrid&, glm::ivec2> m_collided{ [this](ColliderGrid& tag, glm::ivec2 direction) { collided(tag, direction); } };
    stump::Event<int>                               m_scores;
};
