#include "SoundSystemSDL3_Mixer.h"

#include <bitset>
#include <forward_list>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>

class SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl
{
public:
    SoundSystemSDL3_MixerImpl();
    void play(const std::string_view& song_path);

private:
    std::forward_list<std::jthread> m_audio_threads;
};

SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl::SoundSystemSDL3_MixerImpl()
{
    if (!Mix_OpenAudio(0, nullptr))
    {
        std::cerr << "failed loading audio";
    }
}

void SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl::play(const std::string_view& song_path)
{
    m_audio_threads.emplace_front([&]()
    {
        Mix_Chunk* audio_clip = Mix_LoadWAV(std::string(song_path).c_str());
        Mix_PlayChannel(-1, audio_clip, -1);
    });
}


// PUBLIC INTERFACE

SoundSystemSDL3_Mixer::SoundSystemSDL3_Mixer() : m_handler{std::make_unique<SoundSystemSDL3_MixerImpl>()}
{
}

SoundSystemSDL3_Mixer::~SoundSystemSDL3_Mixer() = default;

void SoundSystemSDL3_Mixer::play(const std::string_view& song_path)
{
    m_handler->play(song_path);
}

