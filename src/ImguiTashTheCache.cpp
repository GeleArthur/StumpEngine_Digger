#include "ImguiTashTheCache.h"

#include <algorithm>
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
        m_exercise1_y_data.clear();
        std::vector<int> array_to_mess_with(1000'000'0, 3);
        for (const int skip_index : m_exercise1_x_data)
        {
            std::vector<int> time_record(m_exercise1_samples);
            for (int sample_count = 0; sample_count < m_exercise1_samples; ++sample_count)
            {
                using namespace std::chrono;
                auto start_time = high_resolution_clock::now();
                for (size_t i = 0; i < array_to_mess_with.size(); i += skip_index)
                {
                    array_to_mess_with[i] *= 2;
                }
                auto end_time = high_resolution_clock::now();

                const auto time_it_took = duration_cast<microseconds>(end_time - start_time).count();
                time_record[sample_count] = static_cast<int>(time_it_took);
            }

            std::ranges::sort(time_record);
            auto results = std::ranges::subrange(++time_record.begin(), --time_record.end());
            auto avarage =
                std::accumulate(results.begin(), results.end(), 0)
                / (m_exercise1_samples - 2);

            m_exercise1_y_data.push_back(avarage);
        }
    }


    if (!m_exercise1_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise1 plot"))
        {
            ImPlot::SetupAxesLimits(
                *std::ranges::min_element(m_exercise1_x_data),
                *std::ranges::max_element(m_exercise1_x_data),
                *std::ranges::min_element(m_exercise1_y_data),
                *std::ranges::max_element(m_exercise1_y_data)
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
