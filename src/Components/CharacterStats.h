#pragma once
#include <memory>

#include "Component.h"
#include "../Event.h"
#include "../EventListener.h"


class CharacterStats final : public Component
{
public:
    explicit CharacterStats(GameObject& game_object);

    [[nodiscard]] int get_health() const { return m_health; };
    [[nodiscard]] int get_score() const { return m_score; };

    void remove_health();
    void add_score(int amount);

    Event<int> on_health_changed;
    Event<int> on_score_changed;

private:
    int m_health;
    int m_score;
};
