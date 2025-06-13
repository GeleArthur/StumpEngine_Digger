#pragma once
#include <EventListener.h>
#include <vec2.hpp>
#include <Component/Component.h>

class ColliderGrid;
class Gem final : public stump::Component
{
public:
    explicit Gem(stump::GameObject& attached_game_object, ColliderGrid& collider);
    void collided(uint64_t tag, glm::ivec2 direction) const;

private:
    stump::EventListener<uint64_t, glm::ivec2> m_collided{ [this](uint64_t tag, glm::ivec2 direction) { collided(tag, direction); } };
};
