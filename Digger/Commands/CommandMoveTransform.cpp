#include "CommandMoveTransform.h"

CommandMoveTransform::CommandMoveTransform(Transform& transform):
    m_transform{transform}
{
}

void CommandMoveTransform::execute()
{
}
