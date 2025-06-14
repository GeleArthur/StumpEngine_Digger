#pragma once
#include "../Scene/GameModes.h"

#include <StumpEngine.h>
#include <vector>
#include <Component/Component.h>
#include <Input/InputBinding.h>

namespace stump
{
    class Transform;
    class Scene;
} // namespace stump

class ModeSelectUi final : public stump::Component
{
public:
    explicit ModeSelectUi(stump::GameObject& attached, stump::Scene& scene);
    ~ModeSelectUi() override;
    void pressed(glm::vec2 direction);
    void start_game();

private:
    stump::EventListener<glm::vec2> m_move;
    stump::EventListener<>          m_press_start;
    stump::InputBindingVector       m_move_cursor;
    stump::InputBindingButton       m_game_start;
    stump::Transform*               m_arrow_transform;
    GameModes                       m_selected_game_mode{};
    stump::StumpEngine*             m_engine;
};
