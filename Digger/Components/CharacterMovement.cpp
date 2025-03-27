#include "CharacterMovement.h"

#include <Command.h>
#include <GameObject.h>
#include <iostream>
#include <StumpEngine.h>
#include <Component/Transform.h>


class CommandMove final : public Command
{
public:
    explicit CommandMove(CharacterMovement& character, const glm::vec2 movement): m_character{character}, m_movement(movement)
    {
    }

    virtual void execute() override
    {
        m_character.change_movement(m_movement);
    }

private:
    CharacterMovement& m_character;
    glm::vec2 m_movement;
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
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(-1, 0)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(1, 0)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_UP,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(0, -1)));

        input_handler.bind_gamepad_button(
            SDL_GAMEPAD_BUTTON_DPAD_DOWN,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(0, 1)));
    }
    else
    {
        input_handler.bind_keyboard(
            SDL_SCANCODE_A,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(-1, 0)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_D,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(1, 0)));

        input_handler.bind_keyboard(
            SDL_SCANCODE_W,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(0, -1)));


        input_handler.bind_keyboard(
            SDL_SCANCODE_S,
            input_pressed_type::held_down,
            std::make_unique<CommandMove>(*this, glm::vec2(0, 1)));
    }
}

void CharacterMovement::change_movement(const glm::vec2 movement) const
{
    const float speed = m_is_gamepad ? 100.f : 50.f;
    glm::vec2 current_pos = get_game_object().get_transform().get_local_position();
    current_pos += movement * speed * get_game_object().get_engine().get_time().delta_time;
    get_game_object().get_transform().set_local_position(current_pos);
}
