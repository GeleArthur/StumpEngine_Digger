#pragma once
#include "IGoldBagState.h"

#include <EngineTime.h>

class GoldBagCollectable final : public IGoldBagState
{
public:
    virtual std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;
    virtual void                           collided(ColliderGrid& tag, glm::ivec2 direction) override;

private:
    float m_animation_delay{ stump::EngineTime::instance().get_current_time() + 0.1f };
    int   m_sprite_index{ 0 };
    int   m_colleted{ 0 };
};
