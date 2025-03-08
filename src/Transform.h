#pragma once

#include "Component.h"
#include <glm.hpp>
#include <vector>

class Transform final : public Component
{
public:
	explicit Transform(GameObject& attached_game_object, const glm::vec2& pos);
	~Transform() override;

	void set_parent(Transform& new_parent, bool keep_world_position = false);
	void remove_parent();
	[[nodiscard]] const glm::vec2& get_world_position();
	[[nodiscard]] const glm::vec2& get_local_position() const;
	void set_local_position(const glm::vec2& new_pos);
	std::ranges::subrange<std::vector<std::reference_wrapper<Transform>>::iterator> get_children();

private:
	void remove_child_internal(const Transform& child);
	void add_child_internal(Transform& child);
	bool do_you_have_this_child(Transform& child) const;
	void mark_me_and_children_as_dirty();

	std::vector<std::reference_wrapper<Transform>> m_children;
	Transform* m_parent{};

	glm::vec2 m_local_position;
	glm::vec2 m_world_position;
	bool m_world_position_needs_updating{};
};

