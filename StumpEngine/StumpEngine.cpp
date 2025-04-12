#include <chrono>
#include <exception>

#include "StumpEngine.h"

#include <implot.h>
#include <iostream>
#include <thread>
#include <SDL3/SDL.h>

#include "GameObject.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Sleep/HighResolutionSleep.h"

StumpEngine::StumpEngine(const std::function<void(StumpEngine&)>& function)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		throw std::exception();
	}
	if (!TTF_Init())
	{
		SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
		throw std::exception();
	}

	if (!SDL_CreateWindowAndRenderer("Programming 4 Engine", 640, 480, 0, &m_window, &m_renderer))
	{
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		throw std::exception();
	}

	SDL_DisplayMode** display_info = SDL_GetFullscreenDisplayModes(SDL_GetPrimaryDisplay(), nullptr);
	m_refresh_rate_delay = 1.0 / display_info[0]->refresh_rate;

	IMGUI_CHECKVERSION();
	ImGuiContext* imgui_context = ImGui::CreateContext();
	ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
	ImGui_ImplSDLRenderer3_Init(m_renderer);

	ImPlot::SetImGuiContext(imgui_context);
	ImPlot::CreateContext();

	high_resolution_sleep::init_precise_sleep();

	function(*this);
}

StumpEngine::~StumpEngine()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	ImPlot::DestroyContext();

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

GameObject& StumpEngine::add_game_object()
{
	m_game_objects.push_back(std::make_unique<GameObject>(*this));
	return m_game_objects[m_game_objects.size() - 1].operator*();
}

SDL_Renderer* StumpEngine::get_renderer() const
{
	return m_renderer;
}

const EngineTime& StumpEngine::get_time() const
{
	return m_engine_time;
}

InputHandler& StumpEngine::get_input()
{
	return m_input_handler;
}

AchievementSystem& StumpEngine::get_achievement_system()
{
	return m_achievement_system;
}

void StumpEngine::run()
{
	using namespace std::chrono;
	auto last_time = high_resolution_clock::now();
	const auto start_of_loop = high_resolution_clock::now();

	while (!m_is_quitting)
	{
		auto current = high_resolution_clock::now();
		m_engine_time.delta_time = duration<float>(current - last_time).count();
		m_time_passed += current - last_time;
		last_time = current;
		m_engine_time.current_time = duration<float>(current - start_of_loop).count();

		run_one_loop();

		auto time_to_sleep = current + duration<double>(m_refresh_rate_delay) - high_resolution_clock::now();
		high_resolution_sleep::precise_sleep(time_to_sleep.count() / 1000000000.0);
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

	m_input_handler.process_input();
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
		game_object->render();
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);

	SDL_RenderPresent(m_renderer);
	delete_marked_game_objects();
}

void StumpEngine::delete_marked_game_objects()
{
	for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
	{
		game_object->removed_marked_components();
	}

	std::erase_if(m_game_objects, [](const std::unique_ptr<GameObject>& game_object)
	{
		return game_object->is_marked_for_deletion();
	});
}
