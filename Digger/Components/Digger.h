#pragma once
#include <EventListener.h>
#include <Component/Component.h>
#include <Input/InputBinding.h>
#include <chrono>

class GridTransform;
class Digger final : public stump::Component
{
public:
    explicit Digger(stump::GameObject& attached);

    void update() override;
    void render(SDL_Renderer* renderer) override;
    void press_button();

private:
    stump::InputBindingButton m_button;
    stump::InputBindingVector m_movement;
    stump::EventListener<>    m_button_pressed;
    float                     m_move_delay{};
    glm::vec2                 m_last_move_direction{};
    GridTransform*            m_grid_transform{};
};
