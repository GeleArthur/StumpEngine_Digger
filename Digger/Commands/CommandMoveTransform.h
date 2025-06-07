#pragma once
#include "Command.h"

namespace stump
{
    class Transform;

    class CommandMoveTransform final : public stump::Command
    {
    public:
        explicit CommandMoveTransform(Transform& transform);
        virtual void execute() override;

    private:
        Transform& m_transform;
    };
} // namespace stump
