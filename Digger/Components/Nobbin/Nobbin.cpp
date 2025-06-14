#include "Nobbin.h"

#include "NobbinNormalState.h"
#include "../GridTransform.h"

#include <EngineTime.h>
Nobbin::Nobbin(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid, stump::Texture2DSpriteSheet& sprite_sheet)
    : Component{ attached }
    , m_grid_transform{ (&grid_transform) }
    , m_dirt_grid{ &dirt_grid }
    , m_state{ std::make_unique<NobbinNormalState>(*this) }
    , m_sprite_sheet(&sprite_sheet)
{
}
Nobbin::~Nobbin()
{
}
void Nobbin::update()
{
    std::unique_ptr<INobbinState> new_state = m_state->update();
    if (new_state != nullptr)
    {
        m_state = std::move(new_state);
    }
}