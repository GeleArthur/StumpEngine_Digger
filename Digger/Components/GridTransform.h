#pragma once
#include "Digger.h"
#include "Digger.h"
#include "Digger.h"
#include "Digger.h"

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

    void move(const glm::ivec2& direction);
    template<typename T>
    void move(const T&) = delete;

    bool can_move_direction(const glm::ivec2& direction) const;
    template<typename T>
    bool can_move_direction(const T&) const = delete;

    bool can_move_any_direction() const;

    glm::vec2         get_real_position() const;
    static glm::ivec2 free_direction_to_grid_direction(const glm::vec2& direction);

    stump::Event<glm::ivec2>& get_moved_event();

private:
    void move_horizontal(bool going_left);
    void move_vertical(bool going_down);
    bool can_move_horizontal() const;
    bool can_move_vertical() const;

    glm::ivec2               m_grid_position;
    glm::ivec2               m_sub_position;
    stump::Event<glm::ivec2> m_moved;
};
