#include "ColliderGrid.h"
#include "CollisionHolder.h"
#include "GridTransform.h"

// std::hash<std::string> ColliderGrid::m_hasher{};

ColliderGrid::ColliderGrid(stump::GameObject& attached, GridTransform& grid_transform, CollisionHolder& holder, uint64_t tag)
    : Component{ attached }
    , m_holder{ &holder }
    , m_tag{ tag }
    , m_grid_transform{ &grid_transform }
{
    m_holder->add_collider(*this);
}
ColliderGrid::~ColliderGrid()
{
    if (m_holder != nullptr)
    {
        m_holder->remove_collider(*this);
    }
}
void ColliderGrid::fixed_update()
{
    for (ColliderGrid* transform : m_holder->get_colliders())
    {
        if (transform->m_tag == m_tag)
            continue;

        if (transform->m_grid_transform->get_grid_position() == m_grid_transform->get_grid_position())
        {
            m_collided.notify_listeners(transform->m_tag, transform->m_grid_transform->get_grid_position() - m_grid_transform->get_grid_position());
        }
    }
}
void ColliderGrid::disconnect_holder()
{
    m_holder = nullptr;
    remove_component();
}