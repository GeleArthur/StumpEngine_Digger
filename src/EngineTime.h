#pragma once
#include <chrono>

class Minigin;

class EngineTime
{
public:
    explicit EngineTime();


	float DeltaTime{};
	float CurrentTime{};

private:
	friend Minigin;
	void update();

	std::chrono::time_point<std::chrono::steady_clock> m_start_of_application;
	std::chrono::time_point<std::chrono::steady_clock> m_previous_update;
};
