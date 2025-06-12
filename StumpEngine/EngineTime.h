#pragma once
#include <Singleton.h>
#include <chrono>

namespace stump
{
    class EngineTime : public Singleton<EngineTime>
    {
    public:
        float get_delta_time() const
        {
            return m_delta_time;
        }
        float get_current_time() const
        {
            return m_current_time;
        }

        std::chrono::high_resolution_clock::time_point get_current_time_clock() const
        {
            return m_last_time;
        }

        void update();

    private:
        float m_delta_time{};
        float m_current_time{};

        const std::chrono::high_resolution_clock::time_point m_start_of_loop{ std::chrono::high_resolution_clock::now() };
        std::chrono::high_resolution_clock::time_point       m_last_time{ std::chrono::high_resolution_clock::now() };

        friend Singleton;
        explicit EngineTime() = default;
    };
} // namespace stump
