#pragma once
#include <Singleton.h>
#include <chrono>

namespace stump
{
    class EngineTime : public Singleton<EngineTime>
    {
    public:
        friend Singleton;
        float delta_time{};
        float current_time{};

    private:
        explicit EngineTime() = default;
    };
} // namespace stump
