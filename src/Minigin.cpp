#include <exception>
#include <numbers>

#include "Minigin.h"
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

	SDL_SetRenderVSync(m_renderer, 1);
	function(*this);
}

Minigin::~Minigin()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

GameObject* Minigin::add_game_object()
{
	m_game_objects.push_back(std::make_unique<GameObject>(this));
	return m_game_objects[m_game_objects.size() - 1].get();
}

SDL_Renderer* Minigin::get_renderer() const
{
	return m_renderer;
}

const EngineTime& Minigin::get_time() const
{
	return m_engine_time;
}

SDL_AppResult Minigin::iterate()
{
	m_engine_time.update();
	for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
	{
		game_object->update();
	}

	const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
	const float red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
	const float green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + std::numbers::pi * 2 / 3));
	const float blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + std::numbers::pi * 4 / 3));
	SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

	SDL_RenderClear(m_renderer);

	for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
	{
		game_object->render();
	}

	SDL_RenderPresent(m_renderer);

	delete_marked_game_objects();

	if (m_is_quitting) return SDL_APP_SUCCESS;
	else return SDL_APP_CONTINUE;
}

void Minigin::event(SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		m_is_quitting = true;
	}
}

void Minigin::delete_marked_game_objects()
{
	std::erase_if(m_game_objects, [](const std::unique_ptr<GameObject>& go) { return go->m_marked_for_deletion; });
}
