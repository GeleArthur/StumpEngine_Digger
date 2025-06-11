#pragma once
#include <memory>

#include "SoundSystem.h"

namespace stump
{
    namespace SoundSystemLocator
    {
        void         register_sound_system(std::unique_ptr<SoundSystem> system);
        SoundSystem& get_sound();
    } // namespace SoundSystemLocator
} // namespace stump