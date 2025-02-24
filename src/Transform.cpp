#include "Transform.h"

#include <iostream>

Transform::Transform(GameObject& attached_game_object, const glm::vec2& pos):
    Component(attached_game_object),
    m_local_position(pos),
    m_world_position(pos)
{
}

Transform::~Transform()
{
    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
    }
    for (auto child : m_children)
    {
        child.get().remove_parent();
    }
}

void Transform::set_parent(Transform& new_parent, const bool keep_world_position)
{
    const glm::vec2 old_world_position = get_world_position();

    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
    }

    new_parent.add_child_internal(*this);
    m_parent = &new_parent;
    mark_me_and_children_as_dirty();

    if (keep_world_position)
    {
        const glm::vec2& new_world_position = get_world_position();
        const glm::vec2 offset = old_world_position - new_world_position;
        set_local_position(get_local_position() + offset);
    }
}

void Transform::remove_parent()
{
    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
        m_parent = nullptr;
        mark_me_and_children_as_dirty();
    }
}

void Transform::remove_child_internal(const Transform& child)
{
    std::erase_if(m_children, [&](const std::reference_wrapper<Transform>& element)
    {
        return &element.get() == &child;
    });
}

void Transform::add_child_internal(Transform& child)
{
    m_children.emplace_back(child);
}

void Transform::mark_me_and_children_as_dirty()
{
    m_world_position_needs_updating = true;
    for (std::reference_wrapper<Transform>& child : m_children)
    {
        child.get().mark_me_and_children_as_dirty();
    }
}

const glm::vec2& Transform::get_world_position()
{
    if (m_world_position_needs_updating)
    {
        if (m_parent != nullptr)
        {
            m_world_position = m_local_position + m_parent->get_world_position();
        }
        else
        {
            m_world_position = m_local_position;
        }
        m_world_position_needs_updating = false;
    }

    return m_world_position;
}

const glm::vec2& Transform::get_local_position() const
{
    return m_local_position;
}

void Transform::set_local_position(const glm::vec2& new_pos)
{
    m_local_position = new_pos;
    mark_me_and_children_as_dirty();
}

std::ranges::subrange<std::vector<std::reference_wrapper<Transform>>::iterator> Transform::get_children()
{
    return std::ranges::subrange{m_children};
}

