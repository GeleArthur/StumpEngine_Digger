#include <iostream>

#include "Component.h"

Component::Component(GameObject* attachedGameObject): m_attached_game_object(attachedGameObject)
{
}


void Component::update()
{
}

void Component::render()
{
}
