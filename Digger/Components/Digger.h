#pragma once
#include <Component/Component.h>

class GridTransform;
class Digger final : public Component
{
public:
    explicit Digger(GameObject& attached, GridTransform& gold_bag);

    void update() override;

    GridTransform& gold_bag; // This is bad but I want to go to sleep and need to demo state machine
private:
};
