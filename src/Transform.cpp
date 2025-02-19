#include "Transform.h"

#include <iostream>

Transform::Transform(GameObject& attached_game_object, const glm::vec2& pos): Component(attached_game_object),
                                                                              m_position(pos)
{
}
