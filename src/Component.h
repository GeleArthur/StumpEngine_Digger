#pragma once

class Minigin;
class GameObject;

class Component
{
public:
	explicit Component(GameObject* attachedGameObject);
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

protected:
	GameObject* m_attached_game_object; // Mmmmmm

private:
	friend GameObject;

	virtual void update();
	virtual void render();
};
