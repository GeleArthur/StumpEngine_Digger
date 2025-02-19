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

	GameObject& add_game_object();
	[[nodiscard]] SDL_Renderer* get_renderer() const;
	[[nodiscard]] const EngineTime& get_time() const;

	void run();

private:
	void run_one_loop();
	void delete_marked_game_objects();

	EngineTime m_engine_time;
	int m_refresh_rate_delay{};
	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};
	std::vector<std::unique_ptr<GameObject>> m_game_objects;
	std::chrono::duration<float> m_time_passed{};
	const std::chrono::duration<float, std::milli> m_fixed_update_time = std::chrono::duration<
		float, std::milli>(45.0f);


	bool m_is_quitting{false};
};
