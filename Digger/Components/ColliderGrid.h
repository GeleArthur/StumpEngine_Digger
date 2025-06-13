#pragma once
#include <Event.h>
#include <string>
#include <vec2.hpp>
#include <Component/Component.h>

class GridTransform;
class CollisionHolder;
class ColliderGrid final : public stump::Component
{
public:
    explicit ColliderGrid(stump::GameObject& attached, GridTransform& grid_transform, CollisionHolder& holder, uint64_t tag);
    ~ColliderGrid() override;

    void fixed_update() override;
    void disconnect_holder();

    stump::Event<uint64_t, glm::ivec2>& get_collided()
    {
        return m_collided;
    };

private:
    int              get_sign(int x);
    CollisionHolder* m_holder;
    GridTransform*   m_grid_transform;
    uint64_t         m_tag;

    stump::Event<uint64_t, glm::ivec2> m_collided;

    // static std::hash<std::string> m_hasher;
};
