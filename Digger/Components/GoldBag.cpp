#include "GoldBag.h"

#include "GridTransform.h"

#include <EngineTime.h>
#include <GameObject.h>
#include <Component/Transform.h>

// Idle state
std::unique_ptr<IGoldBagState> GoldBagIdle::update(GoldBag&)
{
    return nullptr;
}

// Push state
GoldBagPushed::GoldBagPushed(const bool going_left)
    : m_going_left{ going_left }
{
}
std::unique_ptr<IGoldBagState> GoldBagPushed::update(GoldBag& bag)
{
    m_time_until_next_move -= stump::EngineTime::instance().delta_time;
    if (m_time_until_next_move < 0.0f)
    {
        m_time_until_next_move = 0.1f;
        bag.get_game_object().get_component<GridTransform>()->move_horizontal(m_going_left);

        if (m_move_count-- < 0)
        {
            return std::make_unique<GoldBagIdle>();
        }
    }

    return nullptr;
}

// Faling state
std::unique_ptr<IGoldBagState> GoldBagFalling::update(GoldBag&)
{
    return nullptr;
}

// GoldBag
GoldBag::GoldBag(stump::GameObject& attached)
    : Component{ attached }
{
    m_current_state = std::make_unique<GoldBagIdle>();
}

void GoldBag::update()
{
    std::unique_ptr<IGoldBagState> new_state = m_current_state->update(*this);

    if (new_state.get() != nullptr)
    {
        m_current_state = std::move(new_state);
    }
}

void GoldBag::pushing(bool going_left)
{
    if (dynamic_cast<GoldBagIdle*>(m_current_state.get())) // :(
    {
        m_current_state = std::make_unique<GoldBagPushed>(going_left);
    }
}
