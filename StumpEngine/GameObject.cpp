#include "GameObject.h"

#include <StumpEngine.h>
#include <vec2.hpp>
#include <Component/Component.h>
#include <Component/Transform.h>

namespace stump
{
    GameObject::GameObject(StumpEngine& engine)
        : m_engine(engine)
    {
        m_components.push_back(std::make_unique<Transform>(*this, glm::vec2{ 0.0f, 0.0f }));
        m_transform = static_cast<Transform*>(m_components[m_components.size() - 1].get());
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

    Transform& GameObject::get_transform() const
    {
        return *m_transform;
    }

    void GameObject::removed_marked_components()
    {
        std::erase_if(m_components, [](auto& comp) { return comp->is_marked_for_delection(); });
    }

    StumpEngine& GameObject::get_engine() const
    {
        return m_engine;
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

    void GameObject::render(SDL_Renderer* renderer) const
    {
        for (const auto& component : m_components)
        {
            component->render(renderer);
        }
    }
} // namespace stump