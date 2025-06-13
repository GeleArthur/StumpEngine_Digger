#pragma once
#include "../GameDataTracker.h"

#include <vec2.hpp>
#include <Component/Component.h>

class Nobbin;
class NobbinAI final : public stump::Component
{
public:
    explicit NobbinAI(stump::GameObject& game_object, Nobbin& nobbin, GameDataTracker& game_data);
    void update() override;

private:
    Nobbin*          m_nobbin;
    glm::ivec2       m_last_move{};
    GameDataTracker* m_data_tracker;
};
