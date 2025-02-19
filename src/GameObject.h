#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component.h"

class Minigin;

class GameObject final
{
public:
	explicit GameObject(Minigin& engine);
	~GameObject() = default;

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	template <typename T, typename... Args> requires std::derived_from<T, Component>
	T& add_component(Args&&... arguments)
	{
		T* component = get_component<T>();
		if (component == nullptr)
		{
			m_components.push_back(std::make_unique<T>(*this, std::forward<Args>(arguments)...));
			component = static_cast<T*>(m_components[m_components.size() - 1].get());
		}

		return *component;
	}

	template <typename T> requires std::derived_from<T, Component>
	[[nodiscard]] T* get_component()
	{
		for (const std::unique_ptr<Component>& component : m_components)
		{
			if (T* component_casted = dynamic_cast<T*>(component.get()); component_casted != nullptr)
			{
				return component_casted;
			}
		}
		return nullptr;
	}

	[[nodiscard]] Minigin& get_engine() const { return m_engine; }
	[[nodiscard]] bool is_marked_for_deletion() const;
	void mark_for_deletion();

	void fixed_update() const;
	void update() const;
	void render() const;

private:
	Minigin& m_engine;

	std::vector<std::unique_ptr<Component>> m_components;
	bool m_marked_for_deletion{false};
};
