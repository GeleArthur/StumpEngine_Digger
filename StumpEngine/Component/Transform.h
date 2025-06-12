#pragma once

#include <Component/Component.h>
#include <glm.hpp>
#include <vector>
namespace stump
{
    class Transform final : public Component
    {
    public:
        explicit Transform(GameObject& attached_game_object, const glm::vec2& pos = {});
        ~Transform() override;

        Transform(const Transform& other) = delete;
        Transform(Transform&& other) = delete;
        Transform& operator=(const Transform& other) = delete;
        Transform& operator=(Transform&& other) = delete;

        using children = std::ranges::subrange<std::vector<std::reference_wrapper<Transform>>::iterator>;

        void                           set_parent(Transform& new_parent, bool keep_world_position = false);
        void                           remove_parent();
        [[nodiscard]] const glm::vec2& get_world_position();
        [[nodiscard]] const glm::vec2& get_local_position() const;
        void                           set_local_position(const glm::vec2& new_pos);
        children                       get_children();

    private:
        void remove_child_internal(const Transform& child);
        void remove_parent_internal();
        void add_child_internal(Transform& child);
        bool do_you_have_this_child(Transform& child) const;
        void mark_me_and_children_as_dirty();

        std::vector<std::reference_wrapper<Transform>> m_children;
        Transform*                                     m_parent{};

        glm::vec2 m_local_position;
        glm::vec2 m_world_position;
        bool      m_world_position_needs_updating{};
        bool      m_parent_should_remove_me{};
    };
} // namespace stump