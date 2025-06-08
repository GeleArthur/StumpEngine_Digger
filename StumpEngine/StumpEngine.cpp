#include <chrono>
#include <exception>
#include <print>

#include "StumpEngine.h"

#include <implot.h>
#include <thread>
#include <SDL3/SDL.h>

#include "GameObject.h"
#include "imgui.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Sleep/HighResolutionSleep.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include <Input/InputManager.h>

namespace stump
{
    StumpEngine::StumpEngine(const std::function<void(StumpEngine&)>& function)
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
        {
            throw std::exception(std::format("Couldn't initialize SDL: {}", SDL_GetError()).c_str());
        }
        if (!TTF_Init())
        {
            throw std::exception(std::format("Couldn't initialize TTF: {}", SDL_GetError()).c_str());
        }

        if (m_window = SDL_CreateWindow("Programming 4 Engine", 960, 600, SDL_WINDOW_HIDDEN); m_window == nullptr)
        {
            throw std::exception(std::format("Couldn't initialize window: {}", SDL_GetError()).c_str());
        }

        if (m_renderer = SDL_CreateRenderer(m_window, nullptr); m_renderer == nullptr)
        {
            throw std::exception(std::format("Couldn't initialize renderer: {}", SDL_GetError()).c_str());
        }
        SDL_ShowWindow(m_window);

        SDL_DisplayMode** display_info = SDL_GetFullscreenDisplayModes(SDL_GetPrimaryDisplay(), nullptr);
        m_refresh_rate_delay = 1.0 / display_info[0]->refresh_rate;

        IMGUI_CHECKVERSION();
        ImGuiContext* imgui_context = ImGui::CreateContext();
        ImGuiIO&      io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
        ImGui_ImplSDLRenderer3_Init(m_renderer);

        ImPlot::SetImGuiContext(imgui_context);
        ImPlot::CreateContext();

        high_resolution_sleep::init_precise_sleep();

        InputManager::instance().fetch_devices();

        function(*this);
    }

    StumpEngine::~StumpEngine()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        ImPlot::DestroyContext();

        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    GameObject& StumpEngine::add_game_object()
    {
        m_game_objects.push_back(std::make_unique<GameObject>(*this));
        return *m_game_objects[m_game_objects.size() - 1];
    }

    SDL_Renderer* StumpEngine::get_renderer() const
    {
        return m_renderer;
    }

    void StumpEngine::run()
    {
        using namespace std::chrono;
        auto       last_time = high_resolution_clock::now();
        const auto start_of_loop = high_resolution_clock::now();

        while (!m_is_quitting)
        {
            auto current = high_resolution_clock::now();
            EngineTime::instance().delta_time = duration<float>(current - last_time).count();
            m_time_passed += current - last_time;
            last_time = current;
            EngineTime::instance().current_time = duration<float>(current - start_of_loop).count();

            run_one_loop();

            duration<double> time_to_sleep =
                current + duration<double>(m_refresh_rate_delay) - high_resolution_clock::now();
            high_resolution_sleep::precise_sleep(time_to_sleep.count());
        }
    }

    void StumpEngine::handle_input()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                m_is_quitting = true;
            }
            ImGui_ImplSDL3_ProcessEvent(&event);
        }

        InputManager::instance().process_input();
    }

    void StumpEngine::run_one_loop()
    {
        handle_input();
        while (m_time_passed > m_fixed_update_time)
        {
            m_time_passed -= m_fixed_update_time;

            for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
            {
                game_object->fixed_update();
            }
        }

        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->update();
        }

        SDL_RenderClear(m_renderer);

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->render(m_renderer);
        }

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        SDL_RenderPresent(m_renderer);
        delete_marked_game_objects();
    }

    void StumpEngine::delete_marked_game_objects()
    {
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->removed_marked_components();
        }

        std::erase_if(m_game_objects,
                      [](const std::unique_ptr<GameObject>& game_object) { return game_object->is_marked_for_deletion(); });
    }
} // namespace stump
