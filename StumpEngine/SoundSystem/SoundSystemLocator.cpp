#include "SoundSystemLocator.h"

namespace
{
    std::unique_ptr<SoundSystem> instance{};
    SoundSystemNull sound_system_null{};
}

namespace SoundSystemLocator
{
    void register_sound_system(std::unique_ptr<SoundSystem> system)
    {
        instance = std::move(system);
    }

    SoundSystem& get_sound()
    {
        if (instance == nullptr)
        {
            return sound_system_null;
        }
        return *instance;
    }
}

