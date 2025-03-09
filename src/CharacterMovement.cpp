#include "CharacterMovement.h"

#include <iostream>

#include "GameObject.h"
#include "Minigin.h"

class CommandMove final : public Command
{
public:
    explicit CommandMove(glm::vec2& pos_ref, glm::vec2 add_with): m_pos{pos_ref}, m_add_with{add_with}
    {
    }

    virtual void execute() override
    {
        m_pos += m_add_with;
    }

private:
    glm::vec2& m_pos;
    glm::vec2 m_add_with;
};


CharacterMovement::CharacterMovement(GameObject& attached_game_object, const bool is_gamepad):
    Component{attached_game_object},
    m_is_gamepad{is_gamepad}
{
    auto& input_handler = attached_game_object.get_engine().get_input();

    if (is_gamepad)
    {
        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_LEFT,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(-1, 0)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_LEFT,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(1, 0)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(1, 0)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(-1, 0)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_UP,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, -1)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_UP,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, 1)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_DOWN,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, 1)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_DOWN,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, -1)));
    }
    else
    {
        input_handler.bind_keyboard(
            SDL_SCANCODE_A,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(-1, 0)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_A,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(1, 0)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_D,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(1, 0)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_D,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(-1, 0)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_W,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, -1)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_W,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, 1)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_S,
            input_pressed_type::pressed_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, 1)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_S,
            input_pressed_type::let_go_this_frame,
            std::make_unique<CommandMove>(m_input_vector, glm::vec2(0, -1)));
    }
}

void CharacterMovement::update()
{
    const float speed = m_is_gamepad ? 100.f : 50.f;
    glm::vec2 current_pos = get_game_object().get_transform().get_local_position();
    current_pos += m_input_vector * speed * get_game_object().get_engine().get_time().delta_time;
    get_game_object().get_transform().set_local_position(current_pos);
}
