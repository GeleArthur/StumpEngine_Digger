#pragma once
#include <Component/Component.h>

class GridTransform;
class CollisionMonitor;
class CollisionSubject final : public stump::Component
{
public:
    explicit CollisionSubject(stump::GameObject& attached, CollisionMonitor& monitor, GridTransform& transform);
    ~CollisionSubject();

    GridTransform& get_transform() const
    {
        return *m_grid_transform;
    }

private:
    CollisionMonitor* m_monitor;
    GridTransform*    m_grid_transform;
};
