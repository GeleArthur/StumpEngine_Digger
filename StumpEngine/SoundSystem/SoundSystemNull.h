#pragma once
#include "SoundSystem.h"
namespace stump
{
    class SoundSystemNull final : public SoundSystem
    {
    public:
        void play(const std::string& song_path, float volume) override;
    };
} // namespace stump