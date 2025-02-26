#include "ImguiTashTheCache.h"

#include <complex>

#include "imgui.h"
#include "implot.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <ranges>


void ImguiTashTheCache::update()
{
    Component::update();
}

void ImguiTashTheCache::render()
{
    ImGui::SetNextWindowSize({400, 450}, ImGuiCond_Appearing);
    ImGui::Begin("Exercise1");

    ImGui::InputInt("Samples", &m_exercise1_samples);
    if (ImGui::Button("Trash The Cache"))
    {
        m_exercise1_x_data.clear();
        m_exercise1_y_data.clear();

        auto results = std::vector<std::vector<long long>>(
            static_cast<int>(std::log2(exercise_power_of_2_max_size) + 1));
        for (std::vector<long long>& arrays : results)
        {
            arrays.resize(m_exercise1_samples);
        }

        auto large_array_of_ints = std::vector<int>(1'000'000'0);
        for (int sample_index = 0; sample_index < m_exercise1_samples; ++sample_index)
        {
            using namespace std::chrono;
            for (auto stepsize = 1; stepsize <= exercise_power_of_2_max_size; stepsize *= 2)
            {
                auto start = high_resolution_clock::now();
                for (int i = 0; i < static_cast<int>(large_array_of_ints.size()); i += stepsize)
                {
                    large_array_of_ints[i] *= 2;
                }
                auto end = high_resolution_clock::now();
                const auto time_took = (end - start).count();

                results[static_cast<int>(std::log2(stepsize))][sample_index] = time_took;
            }
        }

        for (auto stepsize = 1; stepsize <= exercise_power_of_2_max_size; stepsize *= 2)
        {
            m_exercise1_x_data.push_back(stepsize);
        }

        for (int i = 0; i < results.size(); ++i)
        {
            long long average = std::accumulate(results[i].begin(), results[i].end(), 0ll);
            average /= static_cast<long long>(results.size());
            m_exercise1_y_data.push_back(static_cast<int>(average));
        }
    }


    if (!m_exercise1_x_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise1 plot"))
        {
            ImPlot::SetupAxesLimits(
                *std::min_element(m_exercise1_x_data.begin(), m_exercise1_x_data.end()),
                *std::max_element(m_exercise1_x_data.begin(), m_exercise1_x_data.end()),
                *std::min_element(m_exercise1_y_data.begin(), m_exercise1_y_data.end()),
                *std::max_element(m_exercise1_y_data.begin(), m_exercise1_y_data.end())
            );
            ImPlot::PlotLine("Exercise1 line",
                             m_exercise1_x_data.data(),
                             m_exercise1_y_data.data(),
                             static_cast<int>(m_exercise1_y_data.size()));
            ImPlot::EndPlot();
        }
    }

    ImPlot::ShowDemoWindow();

    ImGui::End();
}
