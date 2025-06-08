#include "Digger.h"
#include <GameObject.h>
#include <imgui.h>
#include <Input/InputManager.h>

Digger::Digger(stump::GameObject& attached, GridTransform& gold_bag)
    : Component{ attached }
    , gold_bag{ gold_bag }
    , m_button_pressed{ [&] { press_button(); } }
{
    stump::Event<>* const what = m_button.get_on_pressed();

    m_button.get_on_pressed()->add_listener(&m_button_pressed);

    stump::InputManager::instance().get_keyboard().add_button_binding(m_button, SDL_SCANCODE_W);
    // stump::InputManager::instance().get_devices()[0].add_button_binding(SDL_GAMEPAD_BUTTON_SOUTH, m_button);
    // stump::GamepadDevice& gamepad = stump::InputManager::instance().get_devices()[0];

    // gamepad.add_vector_binding(SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY, m_movement);

    // I don't get the command pattern this kinda sucks
    // get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_D, stump::input_pressed_type::held_down, std::make_unique<DiggerHorizontalCommand>(*this, true));
    // get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_A, stump::input_pressed_type::held_down, std::make_unique<DiggerHorizontalCommand>(*this, false));
    // get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_W, stump::input_pressed_type::held_down, std::make_unique<DiggerVerticalCommand>(*this, false));
    // get_game_object().get_engine().get_input().bind_keyboard(SDL_SCANCODE_S, stump::input_pressed_type::held_down, std::make_unique<DiggerVerticalCommand>(*this, true));
}
void Digger::update()
{
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
