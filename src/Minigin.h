#pragma once
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"

class Minigin final
{
public:
	explicit Minigin();
	~Minigin();

	Minigin(const Minigin&) = delete;
	Minigin(Minigin&&) = delete;
	Minigin operator=(const Minigin&) = delete;
	Minigin operator=(Minigin&&) = delete;

	SDL_AppResult iterate();
	void event(SDL_Event* event);

private:
	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};

	bool m_is_quitting{false};
};
