#include "SoundSystemLocator.h"

#include "SoundSystemNull.h"
namespace stump::SoundSystemLocator
{
    namespace
    {
        std::unique_ptr<SoundSystem> instance{ std::make_unique<SoundSystemNull>() };
    }

    void register_sound_system(std::unique_ptr<SoundSystem> system)
    {
        instance = std::move(system);
    }

    SoundSystem& get_sound()
    {
        return *instance;
    }
} // namespace stump::SoundSystemLocator