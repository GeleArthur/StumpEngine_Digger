#include "CollisionSubject.h"

#include "CollisionMonitor.h"
CollisionSubject::CollisionSubject(stump::GameObject& attached, CollisionMonitor& monitor, GridTransform& transform)
    : Component{ attached }
    , m_monitor{ &monitor }
    , m_grid_transform{ &transform }
{
}
CollisionSubject::~CollisionSubject()
{
    m_monitor->subject_is_deleted(this);
}