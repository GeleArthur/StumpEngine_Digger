#include "GameObject.h"

GameObject::GameObject(Minigin* engine): m_engine(engine)
{

}

void GameObject::mark_for_deletion()
{
	m_marked_for_deletion = true;
}

void GameObject::update() const
{
	for (auto& component : m_components)
	{
		component.second->update();
	}
}

void GameObject::render() const
{
	for (auto& component : m_components)
	{
		component.second->render();
	}
}
