#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <SoundSystem/SoundSystemSDL3_Mixer.h>

#include "../Digger/AchievementSystem.h"
#include "EngineTime.h"
#include "Input/InputHandler.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"

class GameObject;

class StumpEngine final
{
public:
	explicit StumpEngine(const std::function<void(StumpEngine&)>& function);
	~StumpEngine();

	StumpEngine(const StumpEngine&) = delete;
	StumpEngine(StumpEngine&&) = delete;
	StumpEngine operator=(const StumpEngine&) = delete;
	StumpEngine operator=(StumpEngine&&) = delete;

	GameObject& add_game_object();
	[[nodiscard]] SDL_Renderer* get_renderer() const;
	[[nodiscard]] const EngineTime& get_time() const;
	[[nodiscard]] InputHandler& get_input();
	[[nodiscard]] AchievementSystem& get_achievement_system();

	[[nodiscard]] const std::vector<std::unique_ptr<GameObject>>& get_all_game_objects()
	{
		return m_game_objects;
	}

	void run();

private:
	void handle_input();
	void run_one_loop();
	void delete_marked_game_objects();

	EngineTime m_engine_time;
	InputHandler m_input_handler;
	AchievementSystem m_achievement_system{*this};
	double m_refresh_rate_delay{};
	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};
	std::vector<std::unique_ptr<GameObject>> m_game_objects{};
	std::chrono::duration<float> m_time_passed{};
	const std::chrono::duration<float, std::milli> m_fixed_update_time = std::chrono::duration<
		float, std::milli>(45.0f);


	bool m_is_quitting{false};
};
