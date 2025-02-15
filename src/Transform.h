#pragma once

#include "Component.h"
#include <glm.hpp>

class Transform final : public Component
{
public:
	explicit Transform(GameObject* attached_game_object, const glm::vec2& pos);

	glm::vec2 m_position;

private:
};

