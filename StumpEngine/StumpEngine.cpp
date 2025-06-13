#include "StumpEngine.h"
#include <chrono>
#include <exception>
#include <print>

#include <implot.h>
#include <thread>
#include <SDL3/SDL.h>

#include "imgui.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Sleep/HighResolutionSleep.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include <ResourceManager.h>
#include <Scene.h>
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

        if (m_window = SDL_CreateWindow("Programming 4 Engine", m_window_size.x, m_window_size.y, SDL_WINDOW_HIDDEN); m_window == nullptr)
        {
            throw std::exception(std::format("Couldn't initialize window: {}", SDL_GetError()).c_str());
        }

        if (m_renderer = SDL_CreateRenderer(m_window, nullptr); m_renderer == nullptr)
        {
            throw std::exception(std::format("Couldn't initialize renderer: {}", SDL_GetError()).c_str());
        }

        ResourceManager::instance().set_renderer(m_renderer);

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

        SDL_ShowWindow(m_window);
    }

    StumpEngine::~StumpEngine()
    {
        m_scene.reset();

        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        ImPlot::DestroyContext();

        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    SDL_Renderer* StumpEngine::get_renderer() const
    {
        return m_renderer;
    }
    void StumpEngine::set_window_size(int width, int height)
    {
        m_window_size.x = width;
        m_window_size.y = height;

        SDL_SetWindowSize(m_window, width, height);
    }
    const glm::ivec2& StumpEngine::get_window_size() const
    {
        return m_window_size;
    }
    void StumpEngine::set_active_scene(std::unique_ptr<Scene>&& scene)
    {
        m_scene = std::move(scene);
    }

    void StumpEngine::run()
    {
        using namespace std::chrono;

        while (!m_is_quitting)
        {
            EngineTime::instance().update();
            run_one_loop();

            duration<double> time_to_sleep = EngineTime::instance().get_current_time_clock() + duration<double>(m_refresh_rate_delay) - high_resolution_clock::now();
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
        m_time_passed += std::chrono::duration<double>(EngineTime::instance().get_delta_time());

        while (m_time_passed > m_fixed_update_time)
        {
            m_time_passed -= m_fixed_update_time;
            m_scene->fixed_update();
        }

        m_scene->update();

        SDL_RenderClear(m_renderer);

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        m_scene->render();

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        SDL_RenderPresent(m_renderer);

        m_scene->delete_marked_game_objects();
    }

} // namespace stump
