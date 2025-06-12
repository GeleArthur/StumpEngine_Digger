#include "Nobbin.h"

#include "NobbinNormalState.h"
#include "../GridTransform.h"

#include <EngineTime.h>
Nobbin::Nobbin(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid)
    : Component{ attached }
    , m_grid_transform{ (&grid_transform) }
    , m_dirt_grid{ &dirt_grid }
    , m_state{ std::make_unique<NobbinNormalState>(*this) }
{
    for (stump::GamepadDevice& gamepad : stump::InputManager::instance().get_gamepads())
    {
        gamepad.add_vector_binding(m_movement, SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY);
        gamepad.add_vector_sides_binding(m_movement,
                                         SDL_GAMEPAD_BUTTON_DPAD_UP,
                                         SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                         SDL_GAMEPAD_BUTTON_DPAD_LEFT,
                                         SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    }
}
void Nobbin::update()
{
    std::unique_ptr<INobbinState> new_state = m_state->update();
    if (new_state.get() != nullptr)
    {
        m_state = std::move(new_state);
    }
}