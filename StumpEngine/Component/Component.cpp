#include <iostream>

#include <Component/Component.h>
#include <SDL3/SDL_render.h>

stump::Component::Component(GameObject& attached_game_object)
    : m_attached_game_object(attached_game_object)
{
}

stump::GameObject& stump::Component::get_game_object() const
{
    return m_attached_game_object;
}

void stump::Component::fixed_update() {}

void stump::Component::update() {}

void stump::Component::render(SDL_Renderer*) {}

void stump::Component::mark_for_deletion()
{
    m_marked_for_delection = true;
}

bool stump::Component::is_marked_for_delection() const
{
    return m_marked_for_delection;
}
