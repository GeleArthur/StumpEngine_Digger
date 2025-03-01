#pragma once
#include <vector>
#include <array>
#include <ranges>
#include <utility>
#include <numeric>
#include <algorithm>
#include <complex>

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
    static constexpr int exercise_skip_levels{11};
    // Why do you do this to me MSVC
    // static constexpr std::array<int, exercise_skip_levels> m_exercise1_x_data = []()
    // {
    //     std::array<int, exercise_skip_levels> arr{};
    //     std::ranges::copy(
    //         std::views::iota(0, exercise_skip_levels) // Create array from 0,1,2,3...
    //         | std::views::transform([](const int n) { return static_cast<int>(std::pow(2, n)); }),
    //         // 2 of power n each number in the array
    //         arr.begin());
    //
    //     return arr;
    // }();

    std::vector<int> m_exercise1_y_data;
};


