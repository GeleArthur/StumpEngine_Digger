#pragma once
#include <EventListener.h>

class StumpEngine;

class AchievementSystem final
{
public:
    explicit AchievementSystem(StumpEngine& engine);
    void world_is_loaded();

private:
    void on_score_changed(int new_score);
    StumpEngine& m_engine;
    std::vector<EventListener<int>> m_on_score_change;
};

