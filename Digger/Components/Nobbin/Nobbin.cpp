#include "Nobbin.h"

#include "NobbinNormalState.h"
#include "../GetHit.h"
#include "../GridTransform.h"

Nobbin::Nobbin(stump::GameObject& attached, GridTransform& grid_transform, DirtGrid& dirt_grid, stump::Texture2DSpriteSheet& sprite_sheet)
    : Component{ attached }
    , m_grid_transform{ (&grid_transform) }
    , m_dirt_grid{ &dirt_grid }
    , m_state{ std::make_unique<NobbinNormalState>(*this) }
    , m_sprite_sheet(&sprite_sheet)
    , m_die_event{ [this] { die(); } }
    , m_collided{ [this](ColliderGrid& e1, glm::ivec2 e2) { collided(e1, e2); } }
{
    get_game_object().get_component<GetHit>()->get_death_event().add_listener(&m_die_event);
    m_collider = get_game_object().get_component<ColliderGrid>();

    m_collider->get_collided().add_listener(&m_collided);
}
Nobbin::~Nobbin()
{
}
void Nobbin::update()
{
    std::unique_ptr<INobbinState> new_state = m_state->update();
    if (new_state != nullptr)
    {
        m_state = std::move(new_state);
    }
}
void Nobbin::collided(ColliderGrid& thingie, glm::ivec2)
{
    // Omg this sucks
    if (thingie.get_game_object().get_component<Digger>())
    {
        if (auto this_sucks = thingie.get_game_object().get_component<GetHit>())
        {
            this_sucks->get_death_event().notify_listeners();
        }
    }
}