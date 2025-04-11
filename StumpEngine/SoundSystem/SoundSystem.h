#pragma once
#include <bitset>

class SoundSystem
{
public:
    virtual ~SoundSystem() = default;
    virtual void play(const std::string_view& song_path) = 0;
};
