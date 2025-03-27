#pragma once
#include <vector>
#include <array>
#include <ranges>
#include <utility>
#include <numeric>
#include <algorithm>
#include <complex>
#include <chrono>
#include <iostream>

#include <Component/Component.h>

class ImguiTashTheCache final : public Component
{
public:
    explicit ImguiTashTheCache(GameObject& attached_game_object):
        Component(attached_game_object)
    {
    }

    void update() override;
    void render() override;
    void exercise1();
    void exercise2();

private:
    int m_exercise1_samples{10};
    int m_exercise2_samples{100};

    std::vector<int> m_exercise1_y_data;
    std::vector<int> m_exercise2_y_data;
    std::vector<int> m_exercise3_y_data;

    int m_exercise1_max_height{};
    int m_exercise2_max_height{};
    int m_exercise3_max_height{};
    int m_exercise_combined_max_height{};

    template <typename TypeToTest, bool hasID = false>
    static void trash_the_cache(std::vector<int>& output, int sample_count = 10, int objects_count = 2'000'000'0)
    {
        std::vector<TypeToTest> largeArray(objects_count);
        output.clear();
        for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            std::vector<int> array_of_times;
            for (int u = 0; u < sample_count; ++u)
            {
                using namespace std::chrono;
                const auto start = high_resolution_clock::now();

                for (size_t i = 0; i < largeArray.size(); i += stepsize)
                {
                    if constexpr (hasID)
                    {
                        largeArray[i].id *= 2;
                    }
                    else
                    {
                        largeArray[i] *= 2;
                    }
                }
                const auto end = high_resolution_clock::now();
                const auto time_took = duration_cast<microseconds>(end - start).count();

                array_of_times.push_back(static_cast<int>(time_took));
            }

            std::ranges::sort(array_of_times);
            int total = std::accumulate(array_of_times.begin() + 1, array_of_times.end() - 1, 0);
            total = total / (sample_count - 2);

            output.push_back(total);
        }
    }
};


