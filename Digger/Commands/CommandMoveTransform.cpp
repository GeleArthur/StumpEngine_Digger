#include "CommandMoveTransform.h"

#include <Component/Transform.h>

stump::CommandMoveTransform::CommandMoveTransform(Transform& transform)
    : m_transform{ transform }
{
}

void stump::CommandMoveTransform::execute()
{
    m_transform.set_local_position({ 0, 0 });
}
