#include "Digger.h"
#include "GridTransform.h"
#include <GameObject.h>
#include <imgui.h>
#include <Input/InputManager.h>

#include <EngineTime.h>

Digger::Digger(stump::GameObject& attached)
    : Component{ attached }
    , m_button_pressed{ [&] { press_button(); } }
{
    m_button.get_on_pressed()->add_listener(&m_button_pressed);

    stump::InputManager::instance().get_keyboard().add_button_binding(m_button, SDL_SCANCODE_W);
    for (stump::GamepadDevice& gamepad : stump::InputManager::instance().get_gamepads())
    {
        gamepad.add_button_binding(m_button, SDL_GAMEPAD_BUTTON_SOUTH);
        gamepad.add_vector_sides_binding(m_movement,
                                         SDL_GAMEPAD_BUTTON_DPAD_UP,
                                         SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                         SDL_GAMEPAD_BUTTON_DPAD_LEFT,
                                         SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    }
}
void Digger::update()
{
    glm::vec2 out = m_movement.get_current_state();

    if (glm::dot(out, out) > 0.1f)
    {
        if (m_move_delay < stump::EngineTime::instance().current_time)
        {
            m_move_delay = stump::EngineTime::instance().current_time + 0.1f;

            GridTransform* digger_transform = get_game_object().get_component<GridTransform>();

            if (digger_transform->can_move_direction(out))
            {
                digger_transform->move(out);
                m_last_move_direction = out;
            }
            else
            {
                digger_transform->move(m_last_move_direction);
            }
        }
    }
}
void Digger::render(SDL_Renderer* renderer)
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("Digger Information", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Digger Status Window");
    ImGui::End();
}
void Digger::press_button()
{
    std::cout << "HOLY FACK";
}
