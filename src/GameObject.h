#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include "component.h"

class Minigin;

class GameObject final
{
public:
	explicit GameObject(Minigin* engine);
	~GameObject() = default;

	template<typename T, typename... Args> requires std::derived_from<T, Component>
	T* add_component(Args&&... arguments)
	{
		auto component = std::make_unique<T>(this, std::forward<Args>(arguments)...);
		m_components[std::type_index(typeid(T))] = std::move(component); 
		return component.get();
	}

	template<typename T>
	[[nodiscard]] T* get_component()
	{
		if (T component = m_components.find(std::type_index(typeid(T))); component != m_components.end())
		{
			return &component;
		}

		return nullptr;
	}

	[[nodiscard]] Minigin* get_engine() const { return m_engine; }

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	friend Minigin;
	Minigin* m_engine;

	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components{};

	void update();
	void render();
};
