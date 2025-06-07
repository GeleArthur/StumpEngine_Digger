#pragma once
#include <vec2.hpp>
#include <Component/Component.h>

class GridTransform final : public stump::Component
{
public:
    explicit GridTransform(stump::GameObject& attached, glm::ivec2 grid_position = glm::ivec2{ 0, 0 });

    void update() override;

    glm::ivec2 get_grid_position() const
    {
        return m_grid_position;
    };

    void move_horizontal(bool going_left);
    void move_vertical(bool going_down);
    bool can_move_any_direction() const;

    glm::vec2 get_real_position() const;

private:
    constexpr static glm::ivec2 what{ 10, 10 };

    glm::ivec2 m_grid_position;
    glm::ivec2 m_sub_position;
};
