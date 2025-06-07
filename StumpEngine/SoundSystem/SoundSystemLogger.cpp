#include "SoundSystemLogger.h"

#include <iostream>

stump::SoundSystemLogger::SoundSystemLogger(std::unique_ptr<SoundSystem> wrapper)
    : m_wrapper_around{ std::move(wrapper) }
{
}

void stump::SoundSystemLogger::play(const std::string& song_path, const float volume)
{
    std::cout << "Playing song: " << song_path << " volume: " << volume << '\n';
    m_wrapper_around->play(song_path, volume);
}
