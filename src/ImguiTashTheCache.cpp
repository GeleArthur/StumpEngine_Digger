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
    exercise1();
    exercise2();
}

void ImguiTashTheCache::exercise1()
{
    ImGui::SetNextWindowSize({400, 450}, ImGuiCond_Appearing);
    ImGui::Begin("Exercise1");

    ImGui::InputInt("Samples", &m_exercise1_samples);
    if (ImGui::Button("Trash The Cache"))
    {
        trash_the_cache<int, false>(m_exercise1_y_data, m_exercise1_samples);
        /*std::vector<int> largeArray(2'000'000'0);
        m_exercise1_y_data.clear();
        for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            std::vector<int> array_of_times;
            for (int u = 0; u < m_exercise1_samples; ++u)
            {
                using namespace std::chrono;
                const auto start = high_resolution_clock::now();

                for (int i = 0; i < largeArray.size(); i += stepsize)
                {
                    largeArray[i] *= 2;
                }
                const auto end = high_resolution_clock::now();
                const auto time_took = duration_cast<nanoseconds>(end - start).count();

                array_of_times.push_back(static_cast<int>(time_took));
            }

            std::ranges::sort(array_of_times);
            int total = std::accumulate(array_of_times.begin() + 1, array_of_times.end() - 1, 0);
            total = total / (m_exercise1_samples - 2);

            m_exercise1_y_data.push_back(total);
        }*/
    }


    if (!m_exercise1_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise1 plot"))
        {
            ImPlot::SetupAxesLimits(
                0,
                10,
                *std::ranges::min_element(m_exercise1_y_data),
                *std::ranges::max_element(m_exercise1_y_data)
            );
            ImPlot::PlotLine("Exercise1 line",
                             m_exercise1_y_data.data(),
                             static_cast<int>(m_exercise1_y_data.size()));
            ImPlot::EndPlot();
        }
    }

    ImGui::End();
}


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
    Transform3D local = Transform3D{};
    int id{};
};

class Gameobject3DAlt
{
public:
    ~Gameobject3DAlt()
    {
        delete local;
    }

    Transform3D* local = new Transform3D{};
    int id{};
};


void ImguiTashTheCache::exercise2()
{
    ImGui::SetNextWindowSize({400, 450}, ImGuiCond_Appearing);
    ImGui::Begin("Exercise2");

    ImGui::InputInt("Samples", &m_exercise2_samples);
    if (ImGui::Button("Trash The Cache With GameObjects3D"))
    {
        trash_the_cache<Gameobject3D, true>(m_exercise2_y_data, m_exercise2_samples, 10'000);

        /*std::vector<Gameobject3D> largeArray(2'000'000);
        m_exercise2_y_data.clear();
        for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            std::vector<int> array_of_times;
            for (int u = 0; u < m_exercise2_samples; ++u)
            {
                using namespace std::chrono;
                const auto start = high_resolution_clock::now();

                for (int i = 0; i < largeArray.size(); i += stepsize)
                {
                    largeArray[i].id *= 2;
                }
                const auto end = high_resolution_clock::now();
                const auto time_took = duration_cast<nanoseconds>(end - start).count();

                array_of_times.push_back(static_cast<int>(time_took));
            }

            std::ranges::sort(array_of_times);
            int total = std::accumulate(array_of_times.begin() + 1, array_of_times.end() - 1, 0);
            total = total / (m_exercise1_samples - 2);

            m_exercise2_y_data.push_back(total);
        }*/
    }


    if (!m_exercise2_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise2 plot"))
        {
            ImPlot::SetupAxesLimits(
                0,
                10,
                *std::ranges::min_element(m_exercise2_y_data),
                *std::ranges::max_element(m_exercise2_y_data)
            );
            ImPlot::PlotLine("GameObject",
                             m_exercise2_y_data.data(),
                             static_cast<int>(m_exercise2_y_data.size()));
            ImPlot::EndPlot();
        }
    }

    if (ImGui::Button("Trash The Cache With GameObjects3DALT"))
    {
        trash_the_cache<Gameobject3DAlt, true>(m_exercise3_y_data, m_exercise2_samples, 100'000);
    }


    if (!m_exercise3_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise3 plot"))
        {
            ImPlot::SetupAxesLimits(
                0,
                10,
                *std::ranges::min_element(m_exercise3_y_data),
                *std::ranges::max_element(m_exercise3_y_data)
            );
            ImPlot::PlotLine("GameObjectAlt",
                             m_exercise3_y_data.data(),
                             static_cast<int>(m_exercise3_y_data.size()));
            ImPlot::EndPlot();
        }
    }

    if (!m_exercise3_y_data.empty() && !m_exercise2_y_data.empty())
    {
        if (ImPlot::BeginPlot("Combined"))
        {
            ImPlot::SetupAxesLimits(
                0,
                10,
                *std::ranges::min_element(m_exercise2_y_data),
                *std::ranges::max_element(m_exercise2_y_data)
            );
            ImPlot::PlotLine("GameObject",
                             m_exercise2_y_data.data(),
                             static_cast<int>(m_exercise2_y_data.size()));

            ImPlot::PlotLine("GameObjectAlt",
                             m_exercise3_y_data.data(),
                             static_cast<int>(m_exercise3_y_data.size()));
            ImPlot::EndPlot();
        }
    }


    ImGui::End();
}
