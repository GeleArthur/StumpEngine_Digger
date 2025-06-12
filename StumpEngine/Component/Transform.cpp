#include "Transform.h"

#include <iostream>

stump::Transform::Transform(GameObject& attached_game_object, const glm::vec2& pos)
    : Component(attached_game_object)
    , m_local_position(pos)
    , m_world_position(pos)
{
}

stump::Transform::~Transform()
{
    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
    }

    for (auto& child : m_children)
    {
        child.get().remove_parent_internal();
    }

    m_children.clear();
}

void stump::Transform::set_parent(Transform& new_parent, const bool keep_world_position)
{
    if (do_you_have_this_child(new_parent))
    {
        // Maybe we should throw?
        return;
    }
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
        const glm::vec2  offset = old_world_position - new_world_position;
        set_local_position(get_local_position() + offset);
    }
}

void stump::Transform::remove_parent()
{
    if (m_parent != nullptr)
    {
        m_parent->remove_child_internal(*this);
        remove_parent_internal();
        mark_me_and_children_as_dirty();
    }
}

void stump::Transform::remove_child_internal(const Transform& child)
{
    std::erase_if(m_children, [&](const std::reference_wrapper<Transform>& element) {
        return &element.get() == &child;
    });
}
void stump::Transform::remove_parent_internal()
{
    m_parent = nullptr;
    mark_me_and_children_as_dirty();
}

void stump::Transform::add_child_internal(Transform& child)
{
    m_children.emplace_back(child);
}

bool stump::Transform::do_you_have_this_child(Transform& child) const
{
    if (&child == this)
    {
        return true;
    }
    for (auto my_child : m_children)
    {
        if (my_child.get().do_you_have_this_child(child))
        {
            return true;
        }
    }

    return false;
}

void stump::Transform::mark_me_and_children_as_dirty()
{
    m_world_position_needs_updating = true;
    for (std::reference_wrapper<Transform>& child : m_children)
    {
        child.get().mark_me_and_children_as_dirty();
    }
}

const glm::vec2& stump::Transform::get_world_position()
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

const glm::vec2& stump::Transform::get_local_position() const
{
    return m_local_position;
}

void stump::Transform::set_local_position(const glm::vec2& new_pos)
{
    m_local_position = new_pos;
    mark_me_and_children_as_dirty();
}

stump::Transform::children stump::Transform::get_children()
{
    return std::ranges::subrange{ m_children };
}
