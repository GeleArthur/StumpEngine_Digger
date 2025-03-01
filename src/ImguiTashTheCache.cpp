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
    ImGui::SetNextWindowSize({300, 350});
    ImGui::Begin("Exercise1");

    ImGui::InputInt("Samples", &m_exercise1_samples);
    if (ImGui::Button("Trash The Cache"))
    {
        trash_the_cache<int, false>(m_exercise1_y_data, m_exercise1_samples);
        m_exercise1_max_height = *std::ranges::max_element(m_exercise1_y_data);
    }


    if (!m_exercise1_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise1 plot"))
        {
            ImPlot::SetupAxesLimits(0, 10, 0, m_exercise1_max_height);
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
    ImGui::SetNextWindowSize({300, 350}, ImGuiCond_Appearing);
    ImGui::SetNextWindowPos({100, 100}, ImGuiCond_FirstUseEver);
    ImGui::Begin("Exercise2");

    ImGui::InputInt("Samples", &m_exercise2_samples);
    if (ImGui::Button("Trash The Cache With GameObjects3D"))
    {
        trash_the_cache<Gameobject3D, true>(m_exercise2_y_data, m_exercise2_samples, 1000'000);
        m_exercise2_max_height = *std::ranges::max_element(m_exercise2_y_data);
        if (!m_exercise3_y_data.empty())
        {
            m_exercise_combined_max_height = std::max(m_exercise3_max_height, m_exercise2_max_height);
        }
    }

    if (!m_exercise2_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise2 plot"))
        {
            ImPlot::SetupAxesLimits(0, 10, 0, m_exercise2_max_height);
            ImPlot::PlotLine("GameObject",
                             m_exercise2_y_data.data(),
                             static_cast<int>(m_exercise2_y_data.size()));
            ImPlot::EndPlot();
        }
    }

    if (ImGui::Button("Trash The Cache With GameObjects3DALT"))
    {
        trash_the_cache<Gameobject3DAlt, true>(m_exercise3_y_data, m_exercise2_samples, 1000'000);
        m_exercise3_max_height = *std::ranges::max_element(m_exercise3_y_data);
        if (!m_exercise2_y_data.empty())
        {
            m_exercise_combined_max_height = std::max(m_exercise3_max_height, m_exercise2_max_height);
        }
    }


    if (!m_exercise3_y_data.empty())
    {
        if (ImPlot::BeginPlot("Exercise3 plot"))
        {
            ImPlot::SetupAxesLimits(0, 10, 0, m_exercise3_max_height);
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
            ImPlot::SetupAxesLimits(0, 10, 0, m_exercise_combined_max_height);
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
