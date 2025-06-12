#pragma once

#include <memory>
#include <vector>
#include <Component/Component.h>
#include <Component/Transform.h>
#include <SDL3/SDL_render.h>

namespace stump
{
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

        template<typename T, typename... Args>
            requires std::derived_from<T, Component>
        T& add_component(Args&&... arguments)
        {
            std::unique_ptr<T> new_component = std::make_unique<T>(*this, std::forward<Args>(arguments)...);
            m_components.push_back(std::move(new_component));

            return *static_cast<T*>(m_components[m_components.size() - 1].get());
        }

        template<typename T>
            requires std::derived_from<T, Component>
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

        template<typename T>
            requires std::derived_from<T, Component>
        [[nodiscard]] std::vector<T*> get_components()
        {
            std::vector<T*> result;
            for (const std::unique_ptr<Component>& component : m_components)
            {
                if (T* component_casted = dynamic_cast<T*>(component.get()); component_casted != nullptr)
                {
                    result.push_back(component_casted);
                }
            }

            return result;
        }

        void remove_all_components() const
        {
            for (const std::unique_ptr<Component>& component : m_components)
            {
                component->remove_component();
            }
        }

        [[nodiscard]] Transform&   get_transform() const;
        void                       removed_marked_components();
        [[nodiscard]] StumpEngine& get_engine() const;
        [[nodiscard]] bool         is_marked_for_deletion() const;
        void                       mark_for_deletion();

        void fixed_update() const;
        void update() const;
        void render(SDL_Renderer* renderer) const;

    private:
        std::vector<std::unique_ptr<Component>> m_components;

        StumpEngine& m_engine;
        Transform&   m_transform;

        bool m_marked_for_deletion{ false };
    };

} // namespace stump
