#pragma once
#include "SoundSystem.h"

class SoundSystemNull final : public SoundSystem
{
public:
    void play(const std::string_view& song_path, float volume) override;
};
