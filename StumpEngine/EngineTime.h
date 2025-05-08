#pragma once
#include <chrono>

class EngineTime
{
private:
	explicit EngineTime() = default;

public:
	static EngineTime& instance();

	float delta_time{};
	float current_time{};
};

inline EngineTime& EngineTime::instance()
{
	static EngineTime instance;
	return instance;
}
