#pragma once
#include "INobelState.h"

class NobbinNormalState : public INobelState
{
public:
    virtual std::unique_ptr<INobelState> update(Nobbin& nobbin) override;

private:
    float m_move_delay{};
    // GridTransform* m_grid_transform;
    glm::vec2 m_last_move_direction{};
};
