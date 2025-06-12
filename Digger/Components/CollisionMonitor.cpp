#include "CollisionMonitor.h"

#include "CollisionSubject.h"

#include <GameObject.h>
CollisionMonitor::CollisionMonitor(stump::GameObject& attached, GridTransform& grid_transform)
    : Component{ attached }
    , m_grid_transform{ &grid_transform }
{
}
CollisionMonitor::~CollisionMonitor()
{
    for (CollisionSubject& subject : m_subjects)
    {
        // subject.get_game_object().remove_component<>()
    }
}
void CollisionMonitor::update()
{
}