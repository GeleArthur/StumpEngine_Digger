//
// Created by a on 09/03/2025.
//

#include "GameCommands.h"

CommandMoveTransform::CommandMoveTransform(Transform& transform):
    m_transform{transform}
{
}

void CommandMoveTransform::execute()
{
}
