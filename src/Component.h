#pragma once

class GameObject;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;



private:
	friend GameObject;

	virtual void update();
	virtual void render();
};
