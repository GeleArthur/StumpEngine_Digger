#pragma once
#include "SoundSystem.h"

class SoundSystemNull final : public SoundSystem
{
public:
    void play(const std::string& song_path, float volume) override;
};
