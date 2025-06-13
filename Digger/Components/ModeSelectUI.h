#pragma once
#include <vector>
#include <Component/Component.h>
#include <Input/InputBinding.h>

namespace stump
{
    class Transform;
    class Scene;
} // namespace stump

enum class GameModes
{
    singleplayer = 0,
    coop = 1,
    versus = 2,
    count = 3
};

class ModeSelectUi final : public stump::Component
{
public:
    explicit ModeSelectUi(stump::GameObject& attached, stump::Scene& scene);
    void pressed(glm::vec2 direction);
    void start_game();

private:
    stump::EventListener<glm::vec2> m_move;
    stump::EventListener<>          m_press_start;
    stump::InputBindingVector       m_move_cursor;
    stump::InputBindingButton       m_game_start;
    stump::Transform*               m_arrow_transform;
    GameModes                       m_selected_game_mode{};
};
