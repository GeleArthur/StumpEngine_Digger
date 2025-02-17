#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "EngineTime.h"
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
	[[nodiscard]] SDL_Renderer* get_renderer() const;
	[[nodiscard]] const EngineTime& get_time() const;

private:
	friend SDL_AppResult SDL_AppIterate(void* appstate);
	friend SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event);
	SDL_AppResult iterate();
	void event(SDL_Event* event);


	void delete_marked_game_objects();

	EngineTime m_engine_time;
	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};
	std::vector<std::unique_ptr<GameObject>> m_game_objects;

	bool m_is_quitting{false};
};
