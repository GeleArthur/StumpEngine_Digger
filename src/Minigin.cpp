#include <exception>
#include <numbers>

#include "minigin.h"
#include <SDL3/SDL.h>

#include "GameObject.h"

Minigin::Minigin(std::function<void(Minigin&)> function)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		throw std::exception();
	}

	if (!SDL_CreateWindowAndRenderer("Programming 4 Engine", 640, 480, 0, &m_window, &m_renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		throw std::exception();
	}
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

SDL_AppResult Minigin::iterate()
{
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

	if (m_is_quitting) return SDL_APP_SUCCESS;
	else return SDL_APP_CONTINUE;
}

void Minigin::event(SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) {
		m_is_quitting = true;
	}
}
