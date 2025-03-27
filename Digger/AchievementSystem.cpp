#include "AchievementSystem.h"

#include <GameObject.h>
#include <isteamuser.h>
#include <isteamuserstats.h>
#include <StumpEngine.h>

#include "Components/CharacterStats.h"

AchievementSystem::AchievementSystem(StumpEngine& engine):
    m_engine{engine}
{
}

void AchievementSystem::world_is_loaded()
{
    if (nullptr == SteamUserStats() || nullptr == SteamUser())
    {
        std::cerr << "Steam is not loaded\n";
        return;
    }

    const std::vector<std::unique_ptr<GameObject>>& all_objects = m_engine.get_all_game_objects();

    for (const std::unique_ptr<GameObject>& object : all_objects)
    {
        CharacterStats* stats = object->get_component<CharacterStats>();
        if (stats != nullptr)
        {
            EventListener<int>& hi = m_on_score_change.emplace_back(std::bind(&AchievementSystem::on_score_changed, this, std::placeholders::_1));
            stats->on_score_changed.add_listener(&hi);
        }
    }
}

void AchievementSystem::on_score_changed(int new_score)
{
    if (new_score > 500)
    {
        SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
        SteamUserStats()->StoreStats();
        m_on_score_change.clear();
    }
}
