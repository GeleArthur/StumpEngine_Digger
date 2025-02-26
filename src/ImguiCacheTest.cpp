#include "ImguiCacheTest.h"

#include <complex>

#include "imgui.h"
#include "implot.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <ranges>


void ImguiCacheTest::update()
{
    Component::update();
}

void ImguiCacheTest::render()
{
    ImGui::Begin("Exercise1");

    ImGui::InputInt("Samples", &m_exercise1_samples);
    if (ImGui::Button("Trash The Cache"))
    {
        m_exercise1_loop_with.clear();
        m_exercise1_loop_result.clear();

        auto results = std::vector<std::vector<int>>(m_exercise1_samples);

        auto large_array_of_ints = std::vector<int>(1'000'000'0);
        for (int u = 0; u < m_exercise1_samples; ++u)
        {
            using namespace std::chrono;
            for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = high_resolution_clock::now();
                for (int i = 0; i < static_cast<int>(large_array_of_ints.size()); i += stepsize)
                {
                    large_array_of_ints[i] *= 2;
                }
                auto end = high_resolution_clock::now();
                auto time_took = (end - start).count();

                results[u].push_back(static_cast<int>(time_took));
            }
        }

        for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            m_exercise1_loop_with.push_back(stepsize);
        }

        for (int i = 0; i < 11; ++i)
        {
            int average{0};
            for (int j = 0; j < static_cast<int>(results.size()); ++j)
            {
                average += results[j][i];
            }
            average /= static_cast<int>(results.size());
            m_exercise1_loop_result.push_back(average);
        }
    }


    if (m_exercise1_loop_with.size() > 0)
    {
        if (ImPlot::BeginPlot("Exercise1 plot"))
        {
            // ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);
            ImPlot::SetupAxesLimits(
                *std::min_element(m_exercise1_loop_with.begin(), m_exercise1_loop_with.end()),
                *std::max_element(m_exercise1_loop_with.begin(), m_exercise1_loop_with.end()),
                *std::min_element(m_exercise1_loop_result.begin(), m_exercise1_loop_result.end()),
                *std::max_element(m_exercise1_loop_result.begin(), m_exercise1_loop_result.end())
            );

            ImPlot::PlotLine("Exercise1 line",
                             m_exercise1_loop_with.data(),
                             m_exercise1_loop_result.data(),
                             static_cast<int>(m_exercise1_loop_result.size()));
            ImPlot::EndPlot();
        }
    }

    ImPlot::ShowDemoWindow();

    ImGui::End();
}
