#pragma once
#include "INobbinState.h"

#include <vec2.hpp>

class NobbinNormalState final : public INobbinState
{
public:
    explicit NobbinNormalState(Nobbin& nobbin);
    virtual std::unique_ptr<INobbinState> update() override;

private:
    bool    check_wall(glm::ivec2 direction) const;
    float   m_move_delay{};
    Nobbin* m_nobbin;
    // GridTransform* m_grid_transform;
    glm::ivec2 m_last_move_direction{};
};
