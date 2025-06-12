#pragma once
#include <Component/Component.h>

class CollisionMonitor;
class CollisionSubject final : public stump::Component
{
public:
    explicit CollisionSubject(stump::GameObject& attached, CollisionMonitor* monitor);

private:
    CollisionMonitor* m_monitor;
};
