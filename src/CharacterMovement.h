#pragma once
#include <glm.hpp>
#include "Component.h"

class CharacterMovement final : public Component
{
public:
    explicit CharacterMovement(GameObject& attached_game_object, bool is_gamepad);
    ~CharacterMovement() = default;
    CharacterMovement(const CharacterMovement& other) = delete;
    CharacterMovement(CharacterMovement&& other) = delete;
    CharacterMovement& operator=(const CharacterMovement& other) = delete;
    CharacterMovement& operator=(CharacterMovement&& other) = delete;

    void change_movement(glm::vec2 movement) const;

private:
    bool m_is_gamepad;
};
