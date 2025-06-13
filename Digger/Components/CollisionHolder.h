#pragma once
#include "ColliderGrid.h"

#include <vector>
#include <Component/Component.h>

class CollisionHolder final : public stump::Component
{
public:
    explicit CollisionHolder(stump::GameObject& attached);
    ~CollisionHolder();

    const std::vector<ColliderGrid*>& get_colliders();

    void add_collider(ColliderGrid& collider);
    void remove_collider(ColliderGrid& collider);

private:
    std::vector<ColliderGrid*> m_colliders;
};
