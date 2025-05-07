#pragma once
#include <glm.hpp>
#include <Component/Component.h>

class BackGroundDrawer;

class CharacterMovement final : public Component
{
public:
    explicit CharacterMovement(GameObject& attached_game_object, bool is_gamepad, BackGroundDrawer& drawer);
    ~CharacterMovement() override = default;
    CharacterMovement(const CharacterMovement& other) = delete;
    CharacterMovement(CharacterMovement&& other) = delete;
    CharacterMovement& operator=(const CharacterMovement& other) = delete;
    CharacterMovement& operator=(CharacterMovement&& other) = delete;

    void change_movement(glm::vec2 movement) const;

    void update() override;

private:
    bool m_is_gamepad;
    BackGroundDrawer& m_drawer;
};
