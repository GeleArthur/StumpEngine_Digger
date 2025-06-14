#include "Gem.h"

#include "ColliderGrid.h"

#include <GameObject.h>
Gem::Gem(stump::GameObject& attached_game_object, ColliderGrid& collider)
    : Component{ attached_game_object }
{
    collider.get_collided().add_listener(&m_collided);
}
void Gem::collided(const ColliderGrid& tag, glm::ivec2 direction) const
{
    if (tag.get_tag() == 0)
    {
        get_game_object().mark_for_deletion();
    }
}
