#pragma once
#include <Event.h>
#include <vec2.hpp>
#include <vector>
#include <Component/Component.h>

class GridTransform;
class CollisionSubject;
class CollisionMonitor final : public stump::Component
{
public:
    explicit CollisionMonitor(stump::GameObject& attached, GridTransform& grid_transform);
    ~CollisionMonitor();

    virtual void              update() override;
    void                      monitor_grid_transform(GridTransform& other);
    void                      subject_is_deleted(CollisionSubject* subject);
    stump::Event<glm::ivec2>& get_on_collided()
    {
        return m_collided;
    };

private:
    stump::Event<glm::ivec2> m_collided;

    std::vector<CollisionSubject*> m_subjects;
    GridTransform*                 m_grid_transform;
};
