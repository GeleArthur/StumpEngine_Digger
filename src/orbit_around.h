#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

class OrbitAround final : public Component
{
public:
    explicit OrbitAround(GameObject& attached_game_object, float size, float speed):
        Component(attached_game_object),
        m_orbit_size(size),
        m_orbit_speed(speed), m_transform(attached_game_object.get_component<Transform>())
    {
        m_start_pos = m_transform->get_local_position();
    }

    void update() override;

private:
    glm::vec2 m_start_pos{};
    float m_orbit_size;
    float m_orbit_speed;
    Transform* m_transform;
};


