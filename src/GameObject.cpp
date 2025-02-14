#include "GameObject.h"

GameObject::GameObject(Minigin* engine): m_engine(engine)
{

}

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
