﻿#pragma once
#include <bitset>

class SoundSystem
{
public:
    SoundSystem() = default;
    virtual ~SoundSystem() = default;
    SoundSystem(const SoundSystem& other) = delete;
    SoundSystem(SoundSystem&& other) = delete;
    SoundSystem& operator=(const SoundSystem& other) = delete;
    SoundSystem& operator=(SoundSystem&& other) = delete;

    virtual void play(const std::string& song_path, float volume) = 0;
};
