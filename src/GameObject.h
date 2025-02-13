#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include "component.h"

class Minigin;

class GameObject final
{
public:
	GameObject() = default;
	~GameObject() = default;

	template<typename T>
	T* add_component() {
		return (m_components[std::type_index(typeid(T))] = std::make_unique<T>()).get();
	}

	template<typename T>
	[[nodiscard]] T* get_component() {
		if (T component = m_components.find(std::type_index(typeid(T))); component != m_components.end())
		{
			return &component;
		}

		return nullptr;
	}


	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	friend Minigin;
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components{};

	void update();
	void render();
};
