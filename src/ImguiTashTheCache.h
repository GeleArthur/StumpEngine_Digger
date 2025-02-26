#pragma once
#include <vector>
#include "Component.h"

struct TrashTheCacheTransform3D
{
    float matrix[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
};

class TrashTheCacheGameObject
{
public:
    TrashTheCacheTransform3D* local = new TrashTheCacheTransform3D{};
    int id{};
};

class ImguiTashTheCache final : public Component
{
public:
    explicit ImguiTashTheCache(GameObject& attached_game_object):
        Component(attached_game_object)
    {
    }

    void update() override;
    void render() override;

private:
    int m_exercise1_samples{10};
    static constexpr int exercise_power_of_2_max_size{1024};
    std::vector<int> m_exercise1_x_data;
    std::vector<int> m_exercise1_y_data;
};


