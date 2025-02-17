#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component.h"

class Minigin;

class GameObject final
{
public:
	explicit GameObject(Minigin* engine);
	~GameObject() = default;

	template <typename T, typename... Args> requires std::derived_from<T, Component>
	T* add_component(Args&&... arguments)
	{
		m_components[std::type_index(typeid(T))] = std::make_unique<T>(*this, std::forward<Args>(arguments)...);
		return static_cast<T*>((m_components[std::type_index(typeid(T))]).get());
	}

	// You can call get_component and see if it returns a nullptr to check if the component exists.
	template <typename T> requires std::derived_from<T, Component>
	[[nodiscard]] T* get_component()
	{
		if (const auto component = m_components.find(std::type_index(typeid(T))); component != m_components.end())
		{
			return static_cast<T*>(component->second.get());
		}

		return nullptr;
	}

	[[nodiscard]] Minigin* get_engine() const { return m_engine; }
	void mark_for_deletion();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	friend Minigin;
	Minigin* m_engine;

	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components{};
	bool m_marked_for_deletion{false};

	void update() const;
	void render() const;
};
