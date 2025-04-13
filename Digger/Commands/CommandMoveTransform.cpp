#include "CommandMoveTransform.h"

#include <Component/Transform.h>

CommandMoveTransform::CommandMoveTransform(Transform& transform):
    m_transform{transform}
{
}

void CommandMoveTransform::execute()
{
    m_transform.set_local_position({0, 0});
}
