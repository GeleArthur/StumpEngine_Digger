#include "GameObject.h"

#include <StumpEngine.h>
#include <Component/Component.h>
#include <Component/Transform.h>
#include <vec2.hpp>

stump::GameObject::GameObject(StumpEngine& engine)
    : m_engine(engine)
    , m_transform(add_component<Transform>(glm::vec2{ 0.0f, 0.0f }))
{
}

void stump::GameObject::mark_for_deletion()
{
    m_marked_for_deletion = true;
}

void stump::GameObject::fixed_update() const
{
    for (const auto& component : m_components)
    {
        component->fixed_update();
    }
}

stump::Transform& stump::GameObject::get_transform() const
{
    return m_transform;
}

void stump::GameObject::removed_marked_components()
{
    std::erase_if(m_components, [](auto& comp) { return comp->is_marked_for_delection(); });
}

stump::StumpEngine& stump::GameObject::get_engine() const
{
    return m_engine;
}

bool stump::GameObject::is_marked_for_deletion() const
{
    return m_marked_for_deletion;
}

void stump::GameObject::update() const
{
    for (const auto& component : m_components)
    {
        component->update();
    }
}

void stump::GameObject::render(SDL_Renderer* renderer) const
{
    for (const auto& component : m_components)
    {
        component->render(renderer);
    }
}
