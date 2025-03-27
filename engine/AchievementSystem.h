#pragma once
#include "EventListener.h"

class Minigin;

class AchievementSystem final
{
public:
    explicit AchievementSystem(Minigin& engine);
    void world_is_loaded();

private:
    void on_score_changed(int new_score);
    Minigin& m_engine;
    std::vector<EventListener<int>> m_on_score_change;
};

