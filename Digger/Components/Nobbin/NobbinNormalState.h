#pragma once
#include "INobbinState.h"

#include <EngineTime.h>
#include <vec2.hpp>

class NobbinNormalState final : public INobbinState
{
public:
    explicit NobbinNormalState(Nobbin& nobbin);
    virtual std::unique_ptr<INobbinState> update() override;

private:
    float      m_move_delay{};
    float      m_time_before_transform{ stump::EngineTime::instance().current_time + 10 };
    Nobbin*    m_nobbin;
    glm::ivec2 m_last_move_direction{};
};
