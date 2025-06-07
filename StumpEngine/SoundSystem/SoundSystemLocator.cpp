#include "SoundSystemLocator.h"
namespace stump::SoundSystemLocator
{
    namespace
    {
        std::unique_ptr<stump::SoundSystem> instance{ std::make_unique<stump::SoundSystemNull>() };
    }

    void register_sound_system(std::unique_ptr<stump::SoundSystem> system)
    {
        instance = std::move(system);
    }

    stump::SoundSystem& get_sound()
    {
        return *instance;
    }
} // namespace stump::SoundSystemLocator