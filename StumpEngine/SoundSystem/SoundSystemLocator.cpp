#include "SoundSystemLocator.h"


namespace SoundSystemLocator
{
    static std::unique_ptr<SoundSystem> m_instance{};
    static SoundSystemNull m_sound_system_null{};

    void register_sound_system(std::unique_ptr<SoundSystem> system)
    {
        m_instance = std::move(system);
    }

    SoundSystem& GetSound()
    {
        if (m_instance.get() == nullptr)
        {
            return m_sound_system_null;
        }
        return *m_instance;
    }
}

