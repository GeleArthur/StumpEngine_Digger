#pragma once
#include <EventListener.h>
#include <Component/Component.h>
#include <Input/InputBinding.h>
#include <chrono>

namespace stump
{
    class Texture2DSpriteSheet;
}
class GridTransform;
class Digger final : public stump::Component
{
public:
    explicit Digger(stump::GameObject& attached);

    void update() override;
    void player_moved(const glm::ivec2& direction);

private:
    stump::InputBindingVector        m_movement;
    stump::EventListener<glm::ivec2> m_player_moved;
    float                            m_move_delay{};
    glm::ivec2                       m_last_move_direction{};
    GridTransform*                   m_grid_transform{};
    stump::Texture2DSpriteSheet*     m_sprite_sheet{};
};
