#include <exception>
#include <numbers>
#include <chrono>

#include "Minigin.h"

#include <thread>
#include <SDL3/SDL.h>

#include "GameObject.h"
#include "imgui.h"
#include "../cmake-build-wsl/_deps/imgui-src/backends/imgui_impl_sdlrenderer3.h"
#include "backends/imgui_impl_sdl3.h"
#include "SDL3_ttf/SDL_ttf.h"

Minigin::Minigin(std::function<void(Minigin&)> function)
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
	m_refresh_rate_delay = static_cast<int>(1.0f / display_info[0]->refresh_rate * 1000.0f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
	ImGui_ImplSDLRenderer3_Init(m_renderer);


	function(*this);
}

Minigin::~Minigin()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

GameObject& Minigin::add_game_object()
{
	m_game_objects.push_back(std::make_unique<GameObject>(*this));
	return m_game_objects[m_game_objects.size() - 1].operator*();
}

SDL_Renderer* Minigin::get_renderer() const
{
	return m_renderer;
}

const EngineTime& Minigin::get_time() const
{
	return m_engine_time;
}

void Minigin::run()
{
	auto last_time = std::chrono::steady_clock::now();
	const auto start_of_loop = std::chrono::steady_clock::now();

	while (!m_is_quitting)
	{
		auto current = std::chrono::steady_clock::now();
		m_engine_time.delta_time = std::chrono::duration<float>(current - last_time).count();
		m_time_passed += current - last_time;
		last_time = current;
		m_engine_time.current_time = std::chrono::duration<float>(current - start_of_loop).count();

		handle_input();

		run_one_loop();

		auto time_to_sleep = current + std::chrono::milliseconds(m_refresh_rate_delay) -
			std::chrono::steady_clock::now();
		std::this_thread::sleep_for(time_to_sleep);
	}
}

void Minigin::handle_input()
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
}

void Minigin::run_one_loop()
{
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

	for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
	{
		game_object->render();
	}

	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);


	SDL_RenderPresent(m_renderer);

	delete_marked_game_objects();
}

void Minigin::delete_marked_game_objects()
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
