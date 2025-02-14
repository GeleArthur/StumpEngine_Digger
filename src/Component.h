#pragma once

class GameObject;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	GameObject* AttachedGameObject; // Mmmmmm

private:
	friend GameObject;

	virtual void update();
	virtual void render();
};
