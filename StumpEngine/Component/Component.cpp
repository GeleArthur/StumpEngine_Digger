#include <iostream>

#include <Component/Component.h>

Component::Component(GameObject& attached_game_object): m_attached_game_object(attached_game_object)
{
}

GameObject& Component::get_game_object() const
{
    return m_attached_game_object;
}


void Component::fixed_update()
{
}

void Component::update()
{
}

void Component::render()
{
}

void Component::mark_for_deletion()
{
    m_marked_for_delection = true;
}

bool Component::is_marked_for_delection() const
{
    return m_marked_for_delection;
}
