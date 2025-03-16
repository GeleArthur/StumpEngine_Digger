#pragma once
#include <memory>

#include "Component.h"
#include "../Event.h"
#include "../EventListener.h"


class CharacterHealth final : public Component
{
public:
    explicit CharacterHealth(GameObject& game_object, int start_health);

    void remove_health();

    Event<int> on_health_changed;

private:
    int m_health;
};
