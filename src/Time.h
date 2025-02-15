#pragma once
#include <chrono>

class Minigin;

class Time
{
public:
    explicit Time();


	float DeltaTime{};
	float CurrentTime{};

private:
	friend Minigin;
	void update();

	std::chrono::time_point<std::chrono::steady_clock> m_start_of_application;
	std::chrono::time_point<std::chrono::steady_clock> m_previous_update;
};
