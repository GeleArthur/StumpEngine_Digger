//
// Created by a on 12/04/2025.
//

#include "SoundSystemLogger.h"

#include <iostream>

SoundSystemLogger::SoundSystemLogger(std::unique_ptr<SoundSystem> wrapper):
    m_wrapper_around{std::move(wrapper)}
{
}

void SoundSystemLogger::play(const std::string_view& song_path, float volume)
{
    std::cout << "Playing song: " << song_path << '\n';
    m_wrapper_around->play(song_path, volume);
}
