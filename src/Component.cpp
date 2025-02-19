#include <iostream>

#include "Component.h"

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
