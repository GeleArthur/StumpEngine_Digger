#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <Component/Component.h>

class Transform;
class StumpEngine;

class GameObject final
{
public:
	explicit GameObject(StumpEngine& engine);
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
			auto does_crash = std::make_unique<T>(*this, std::forward<Args>(arguments)...);
			m_components.push_back(std::move(does_crash));
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

	template <typename T> requires std::derived_from<T, Component>
	void remove_component()
	{
		T* component = get_component<T>();
		if (component != nullptr)
		{
			component->mark_for_delection();
		}
	}

	[[nodiscard]] Transform& get_transform() const;
	void removed_marked_components();
	[[nodiscard]] StumpEngine& get_engine() const;
	[[nodiscard]] bool is_marked_for_deletion() const;
	void mark_for_deletion();

	void fixed_update() const;
	void update() const;
	void render() const;

private:
	std::vector<std::unique_ptr<Component>> m_components;

	StumpEngine& m_engine;
	Transform& m_transform;

	bool m_marked_for_deletion{false};
};
