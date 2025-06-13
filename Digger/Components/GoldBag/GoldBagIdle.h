#pragma once
#include "IGoldBagState.h"

#include <memory>

class GoldBag;
class GoldBagIdle final : public IGoldBagState
{
public:
    std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;

    virtual void collided(uint64_t tag, glm::ivec2 direction) override;

private:
    glm::ivec2 m_direction{};
    bool       m_swap_to_pushed{};
};