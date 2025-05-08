#include "DiggerMoveCommand.h"

#include <EngineTime.h>
#include <GameObject.h>
#include <Component/Transform.h>

DiggerMoveCommand::DiggerMoveCommand(Digger& digger):
    m_digger{digger},
    m_current_time{EngineTime::instance().current_time}
{
}

void DiggerMoveCommand::execute()
{
    glm::vec2 current_pos = m_digger.get_game_object().get_transform().get_local_position();

    if (m_current_time < EngineTime::instance().current_time)
    {
        m_digger.get_game_object().get_transform().set_local_position(current_pos + glm::vec2{10, 0});
        m_current_time = EngineTime::instance().current_time + 0.1f;
    }
}
