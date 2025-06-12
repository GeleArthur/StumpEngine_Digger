#pragma once
#include <vector>
#include <Component/Component.h>

class GridTransform;
class CollisionSubject;
class CollisionMonitor final : public stump::Component
{
public:
    explicit CollisionMonitor(stump::GameObject& attached, GridTransform& grid_transform);
    ~CollisionMonitor();
    virtual void update() override;

private:
    std::vector<CollisionSubject> m_subjects;
    GridTransform*                m_grid_transform;
};
