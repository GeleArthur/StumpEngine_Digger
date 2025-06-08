#pragma once
#include <chrono>

namespace stump
{
    class EngineTime
    {
    public:
        static EngineTime& instance();

        float delta_time{};
        float current_time{};

    private:
        explicit EngineTime() = default;
    };
} // namespace stump
