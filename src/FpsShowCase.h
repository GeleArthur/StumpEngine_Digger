#pragma once
#include <chrono>

#include "Component.h"

class FpsShowcase final : public Component
{
public:
	explicit FpsShowcase(GameObject& attached_game_object);


	FpsShowcase(const FpsShowcase& other) = delete;
	FpsShowcase(FpsShowcase&& other) = delete;
	FpsShowcase& operator=(const FpsShowcase& other) = delete;
	FpsShowcase& operator=(FpsShowcase&& other) = delete;

private:
	void update() override;

	std::chrono::time_point<std::chrono::steady_clock> m_previous;
};
