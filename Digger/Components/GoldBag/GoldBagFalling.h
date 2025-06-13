#pragma once
#include "IGoldBagState.h"

#include <EngineTime.h>
#include <memory>

class GoldBagFalling final : public IGoldBagState
{
public:
    virtual std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;
    void                                   collided(uint64_t tag, glm::ivec2 direction) override;

private:
    float m_move_delay{ stump::EngineTime::instance().get_current_time() };
    int   m_animation_index{ 0 };
    float m_start_delay{ stump::EngineTime::instance().get_current_time() + 2.0f };
    int   m_blocks_fallen{};
};