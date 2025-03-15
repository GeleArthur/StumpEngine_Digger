#pragma once
#include <memory>

#include "Component.h"
#include "../EventListener.h"


class CharacterHealth final : public Component
{
public:
    explicit CharacterHealth(GameObject& game_object);

private:
    std::unique_ptr<void*> m_player_has_damaged;
};
