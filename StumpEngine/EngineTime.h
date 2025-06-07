#pragma once
#include <chrono>

namespace stump
{
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
} // namespace stump