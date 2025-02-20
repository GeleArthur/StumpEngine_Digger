#include "Transform.h"

#include <iostream>

Transform::Transform(GameObject& attached_game_object, const glm::vec2& pos): Component(attached_game_object),
                                                                              m_local_position(pos),
                                                                              m_world_position(pos)
{
}

void Transform::set_parent(Transform& new_parent)
{
    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
    }

    new_parent.add_child_internal(*this);
    m_parent = &new_parent;
    m_world_position_needs_updating = true;
}

void Transform::remove_parent()
{
    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
        m_parent = nullptr;
        m_world_position_needs_updating = true;
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

void Transform::mark_children_as_dirty()
{
    m_world_position_needs_updating = true;
    for (std::reference_wrapper<Transform>& child : m_children)
    {
        child.get().mark_children_as_dirty();
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
    mark_children_as_dirty();
}

