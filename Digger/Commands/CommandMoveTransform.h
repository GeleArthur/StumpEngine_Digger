#pragma once
#include "Command.h"

class Transform;

class CommandMoveTransform final : public Command
{
public:
    explicit CommandMoveTransform(Transform& transform);
    virtual void execute() override;

private:
    Transform& m_transform;
};
