#include <EngineTime.h>

using namespace std::chrono;

void stump::EngineTime::update()
{
    const auto current = high_resolution_clock::now();

    m_delta_time = duration<float>(current - m_last_time).count();
    m_current_time = duration<float>(current - m_start_of_loop).count();

    m_last_time = current;
}
