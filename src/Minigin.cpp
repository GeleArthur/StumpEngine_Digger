#include <exception>
#include <numbers>

#include "minigin.h"
#include <SDL3/SDL.h>

Minigin::Minigin()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		throw std::exception();
	}

	if (!SDL_CreateWindowAndRenderer("Programming 4 Engine", 640, 480, 0, &m_window, &m_renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		throw std::exception();
	}
}

Minigin::~Minigin()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

SDL_AppResult Minigin::iterate()
{
	const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
	/* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
	const float red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
	const float green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + std::numbers::pi * 2 / 3));
	const float blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + std::numbers::pi * 4 / 3));
	SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(m_renderer);

	/* put the newly-cleared rendering on the screen. */
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
