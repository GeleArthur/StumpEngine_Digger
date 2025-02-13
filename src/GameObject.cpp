#include "GameObject.h"

void GameObject::update()
{
	for (auto& component : m_components)
	{
		component.second->update();
	}
}

void GameObject::render()
{
	for (auto& component : m_components)
	{
		component.second->render();
	}
}
