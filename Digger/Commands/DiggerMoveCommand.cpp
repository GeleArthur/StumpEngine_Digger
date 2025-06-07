#include "DiggerMoveCommand.h"

#include "../Components/GoldBag.h"
#include "../Components/GridTransform.h"

#include <EngineTime.h>
#include <GameObject.h>
#include <Component/Transform.h>

DiggerHorizontalCommand::DiggerHorizontalCommand(Digger& digger, bool left)
    : m_digger{ digger }
    , m_current_time{ stump::EngineTime::instance().current_time }
    , m_move{ left }
{
}

void DiggerHorizontalCommand::execute()
{
    if (m_current_time < stump::EngineTime::instance().current_time)
    {
        GridTransform* digger_transform = m_digger.get_game_object().get_component<GridTransform>();
        digger_transform->move_horizontal(m_move);
        m_current_time = stump::EngineTime::instance().current_time + 0.1f;

        if (m_digger.gold_bag.get_grid_position() == digger_transform->get_grid_position())
        {
            m_digger.gold_bag.get_game_object().get_component<GoldBag>()->pushing(m_move);
        }
    }
}

DiggerVerticalCommand::DiggerVerticalCommand(Digger& digger, bool down)
    : m_digger{ digger }
    , m_current_time{ stump::EngineTime::instance().current_time }
    , m_move{ down }
{
}
void DiggerVerticalCommand::execute()
{
    if (m_current_time < stump::EngineTime::instance().current_time)
    {
        m_digger.get_game_object().get_component<GridTransform>()->move_vertical(m_move);
        m_current_time = stump::EngineTime::instance().current_time + 0.1f;
    }
}
