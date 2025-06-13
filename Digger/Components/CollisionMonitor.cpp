#include "CollisionMonitor.h"

#include "CollisionSubject.h"
#include "GridTransform.h"

#include <GameObject.h>
CollisionMonitor::CollisionMonitor(stump::GameObject& attached, GridTransform& grid_transform)
    : Component{ attached }
    , m_grid_transform{ &grid_transform }
{
}
CollisionMonitor::~CollisionMonitor()
{
    for (CollisionSubject* subject : m_subjects)
    {
        subject->remove_component();
    }
}
void CollisionMonitor::update()
{
    for (const CollisionSubject* subject : m_subjects)
    {
        if (subject->get_transform().get_grid_position() == m_grid_transform->get_grid_position())
        {
            m_collided.notify_listeners(subject->get_transform().get_grid_position() - m_grid_transform->get_grid_position());
        }
    }
}
void CollisionMonitor::monitor_grid_transform(GridTransform& other)
{
    CollisionSubject& subject = other.get_game_object().add_component<CollisionSubject>(*this, other);
    m_subjects.push_back(&subject);
}
void CollisionMonitor::subject_is_deleted(CollisionSubject* subject)
{
    m_subjects.erase(std::ranges::find(m_subjects, subject));
}