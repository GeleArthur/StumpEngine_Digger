#include "GoldBagPushed.h"

#include "GoldBagIdle.h"

#include <EngineTime.h>

// Push state
GoldBagPushed::GoldBagPushed(glm::ivec2 direction)
{
}
std::unique_ptr<IGoldBagState> GoldBagPushed::update(GoldBag& bag)
{
    return nullptr;
}

void GoldBagPushed::collided(uint64_t tag, glm::ivec2 direction)
{
}
