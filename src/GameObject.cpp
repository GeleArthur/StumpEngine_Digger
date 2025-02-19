#include "GameObject.h"

#include "Texture2D.h"

GameObject::GameObject(Minigin& engine): m_engine(engine)
{
}

void GameObject::mark_for_deletion()
{
	m_marked_for_deletion = true;
}

void GameObject::fixed_update() const
{
	for (const auto& component : m_components)
	{
		component->fixed_update();
	}
}

bool GameObject::is_marked_for_deletion() const
{
	return m_marked_for_deletion;
}

void GameObject::update() const
{
	for (const auto& component : m_components)
	{
		component->update();
	}
}

void GameObject::render() const
{
	for (const auto& component : m_components)
	{
		component->render();
	}
}
