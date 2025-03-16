//
// Created by a on 13/03/2025.
//

#include "CharacterHealth.h"

#include "../GameObject.h"
#include "../Minigin.h"

class HurtPlayerCommand : public Command
{
public:
    explicit HurtPlayerCommand(CharacterHealth& character): m_character(character)
    {
    }

    void execute() override
    {
        m_character.remove_health();
    }

private:
    CharacterHealth& m_character;
};

CharacterHealth::CharacterHealth(GameObject& game_object, int start_health):
    Component{game_object},
    m_health{start_health}
{
    game_object.get_engine().get_input().bind_keyboard(
        SDL_SCANCODE_E,
        input_pressed_type::pressed_this_frame,
        std::make_unique<HurtPlayerCommand>(*this));
}

void CharacterHealth::remove_health()
{
    --m_health;
    on_health_changed.notify_listeners(m_health);
}
