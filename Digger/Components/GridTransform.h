#pragma once
#include <Event.h>
#include <EventListener.h>
#include <vec2.hpp>
#include <Component/Component.h>

class GridTransform final : public stump::Component
{
public:
    explicit GridTransform(stump::GameObject& attached, glm::ivec2 grid_position = glm::ivec2{ 0, 0 });

    void update() override;

    [[nodiscard]] glm::ivec2 get_grid_position() const
    {
        return m_grid_position;
    };

    [[nodiscard]] glm::ivec2 get_sub_position() const
    {
        return m_sub_position;
    };

    void move_horizontal(bool going_left);
    void move_vertical(bool going_down);
    void move(glm::vec2 direction);
    bool can_move_direction(const glm::vec2& direction) const;
    bool can_move_any_direction() const;
    bool can_move_horizontal() const;
    bool can_move_vertical() const;

    glm::vec2 get_real_position() const;

    stump::Event<glm::ivec2>& get_moved_event();

private:
    glm::ivec2               m_grid_position;
    glm::ivec2               m_sub_position;
    stump::Event<glm::ivec2> m_moved;
};
