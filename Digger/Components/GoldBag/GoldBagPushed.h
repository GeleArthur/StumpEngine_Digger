#pragma once
#include "IGoldBagState.h"
#include <memory>

class GoldBagPushed final : public IGoldBagState
{
public:
    explicit GoldBagPushed(glm::ivec2 direction);
    std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;

    virtual void collided(uint64_t tag, glm::ivec2 direction) override;

private:
};