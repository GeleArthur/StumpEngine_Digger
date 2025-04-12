#pragma once
#include <memory>

#include "SoundSystem.h"
#include "SoundSystemNull.h"

namespace SoundSystemLocator
{
    void register_sound_system(std::unique_ptr<SoundSystem> system);
    SoundSystem& GetSound();
}
