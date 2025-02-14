#include <iostream>

#include "component.h"

Component::Component(GameObject* attachedGameObject): AttachedGameObject(attachedGameObject)
{
}


void Component::update()
{
}

void Component::render()
{
}
