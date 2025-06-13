#pragma once
#include <memory>
#include <vec2.hpp>

class GoldBag;
class IGoldBagState
{
public:
    virtual ~IGoldBagState() = default;
    virtual std::unique_ptr<IGoldBagState> update(GoldBag& bag) = 0;

    virtual void collided(uint64_t tag, glm::ivec2 direction) = 0;
};
