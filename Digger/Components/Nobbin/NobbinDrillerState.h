#pragma once
#include "INobbinState.h"

#include <EngineTime.h>
#include <vec2.hpp>

class NobbinDrillerState final : public INobbinState
{
public:
    explicit NobbinDrillerState(Nobbin& nobbin);
    virtual std::unique_ptr<INobbinState> update() override;

private:
    void       look_direction(glm::ivec2 direction);
    float      m_move_delay{};
    float      m_time_before_transform{ stump::EngineTime::instance().get_current_time() + 4 };
    Nobbin*    m_nobbin;
    glm::ivec2 m_last_move_direction{};
};
