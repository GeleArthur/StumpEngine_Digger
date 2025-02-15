#include "Time.h"

#include <chrono>

Time::Time(): m_start_of_application(std::chrono::steady_clock::now()), m_previous_update(std::chrono::steady_clock::now())
{
}

void Time::update()
{
	auto current = std::chrono::steady_clock::now();
	CurrentTime = std::chrono::duration<float>(current - m_start_of_application).count();
	DeltaTime = std::chrono::duration<float>(current - m_previous_update).count();

	m_previous_update = current;

}
