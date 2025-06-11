#include "Nobbin.h"

#include "../GridTransform.h"

#include <EngineTime.h>
Nobbin::Nobbin(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid)
    : Component{ attached }
    , m_grid_transform{ (&grid_transform) }
{
}
void Nobbin::update()
{
}