#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"

class GameObject;

class Minigin final
{
public:
	explicit Minigin(std::function<void(Minigin&)> function);
	~Minigin();

	Minigin(const Minigin&) = delete;
	Minigin(Minigin&&) = delete;
	Minigin operator=(const Minigin&) = delete;
	Minigin operator=(Minigin&&) = delete;

	GameObject* add_game_object();

	// TODO: Find a solution to move these to private.
	// Can't right now because of the SDL main definition
	SDL_AppResult iterate();
	void event(SDL_Event* event);

private:
	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};
	std::vector<std::unique_ptr<GameObject>> m_game_objects;

	bool m_is_quitting{false};
};
