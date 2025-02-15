#include <iostream>

#include "Component.h"

Component::Component(GameObject* attached_game_object): m_attached_game_object(attached_game_object)
{
}


void Component::update()
{
}

void Component::render()
{
}
