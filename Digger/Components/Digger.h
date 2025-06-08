#pragma once
#include <EventListener.h>
#include <Component/Component.h>
#include <Input/InputBinding.h>

class GridTransform;
class Digger final : public stump::Component
{
public:
    explicit Digger(stump::GameObject& attached, GridTransform& gold_bag);

    void         update() override;
    virtual void render(SDL_Renderer* renderer) override;
    void         press_button();

    GridTransform& gold_bag; // This is bad but I want to go to sleep and need to demo state machine
private:
    stump::InputBindingButton m_button;
    stump::InputBindingVector m_movement;
    stump::EventListener<>    m_button_pressed;
};
