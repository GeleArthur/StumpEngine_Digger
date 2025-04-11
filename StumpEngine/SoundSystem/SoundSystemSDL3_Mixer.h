#pragma once
#include <memory>
#include "SoundSystem.h"


class SoundSystemSDL3_Mixer final : SoundSystem
{
public:
    SoundSystemSDL3_Mixer();
    ~SoundSystemSDL3_Mixer() override;

    SoundSystemSDL3_Mixer(const SoundSystemSDL3_Mixer& other) = delete;
    SoundSystemSDL3_Mixer(SoundSystemSDL3_Mixer&& other) = delete;
    SoundSystemSDL3_Mixer& operator=(const SoundSystemSDL3_Mixer& other) = delete;
    SoundSystemSDL3_Mixer& operator=(SoundSystemSDL3_Mixer&& other) = delete;

    void play(const std::string_view& song_path) override;

private:
    class SoundSystemSDL3_MixerImpl;
    std::unique_ptr<SoundSystemSDL3_MixerImpl> m_handler;
};

