#include <exception>
#include <numbers>

#include "Minigin.h"

#include <thread>
#include <SDL3/SDL.h>

#include "GameObject.h"
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

	function(*this);
}

Minigin::~Minigin()
{
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
	auto last_time = std::chrono::high_resolution_clock::now();
	const auto start_of_loop = std::chrono::high_resolution_clock::now();

	while (!m_is_quitting)
	{
		auto current = std::chrono::steady_clock::now();
		m_engine_time.delta_time = std::chrono::duration<float>(current - last_time).count();
		m_time_passed += current - last_time;
		last_time = current;
		m_engine_time.current_time = std::chrono::duration<float>(current - start_of_loop).count();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				m_is_quitting = true;
			}
		}

		run_one_loop();

		auto time_to_sleep = current + std::chrono::milliseconds(m_refresh_rate_delay) -
			std::chrono::steady_clock::now();
		std::this_thread::sleep_for(time_to_sleep);
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

	SDL_RenderPresent(m_renderer);

	delete_marked_game_objects();
}

void Minigin::delete_marked_game_objects()
{
	std::erase_if(m_game_objects, [](const std::unique_ptr<GameObject>& game_object)
	{
		return game_object->is_marked_for_deletion();
	});
}
