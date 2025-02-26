#pragma once
#include <vector>
#include "Component.h"

struct Transform3D
{
    float matrix[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
};

class Gameobject3D
{
public:
    Transform3D* local = new Transform3D{};
    int id{};
};

class ImguiCacheTest final : public Component
{
public:
    explicit ImguiCacheTest(GameObject& attached_game_object):
        Component(attached_game_object)
    {
    }

    void update() override;
    void render() override;

private:
    int m_exercise1_samples{10};
    std::vector<int> m_exercise1_loop_with;
    std::vector<int> m_exercise1_loop_result;
};
