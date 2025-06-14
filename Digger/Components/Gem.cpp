#include "Gem.h"

#include "ColliderGrid.h"
#include "GameDataTracker.h"

#include <GameObject.h>
Gem::Gem(stump::GameObject& attached_game_object, ColliderGrid& collider, GameDataTracker& tacker)
    : Component{ attached_game_object }
{
    tacker.add_score(m_scores);
    collider.get_collided().add_listener(&m_collided);
}
void Gem::collided(const ColliderGrid& tag, glm::ivec2 direction)
{
    if (tag.get_tag() == 0)
    {
        get_game_object().mark_for_deletion();
        m_scores.notify_listeners(25);
    }
}
