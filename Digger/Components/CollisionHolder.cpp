#include "CollisionHolder.h"
CollisionHolder::CollisionHolder(stump::GameObject& attached)
    : Component{ attached }
{
}
CollisionHolder::~CollisionHolder()
{
    for (ColliderGrid* collider : m_colliders)
    {
        collider->disconnect_holder();
    }
}
const std::vector<ColliderGrid*>& CollisionHolder::get_colliders()
{
    return m_colliders;
}
void CollisionHolder::add_collider(ColliderGrid& collider)
{
    m_colliders.push_back(&collider);
}
void CollisionHolder::remove_collider(ColliderGrid& collider)
{
    m_colliders.erase(std::ranges::find(m_colliders, &collider));
}