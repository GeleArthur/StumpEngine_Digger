#include "SoundSystemSDL3_Mixer.h"

#include <condition_variable>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>

#include "SoundSystemLocator.h"

struct AudioEvent
{
    std::string sound_path;
    float volume;
};

class SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl final
{
public:
    SoundSystemSDL3_MixerImpl();
    ~SoundSystemSDL3_MixerImpl();

    SoundSystemSDL3_MixerImpl(const SoundSystemSDL3_MixerImpl& other) = delete;
    SoundSystemSDL3_MixerImpl(SoundSystemSDL3_MixerImpl&& other) = delete;
    SoundSystemSDL3_MixerImpl& operator=(const SoundSystemSDL3_MixerImpl& other) = delete;
    SoundSystemSDL3_MixerImpl& operator=(SoundSystemSDL3_MixerImpl&& other) = delete;

    void play(const std::string& song_path, float volume);

private:
    void audio_processor();

    std::unordered_map<std::string, Mix_Chunk*> m_loaded_audio;

    std::queue<AudioEvent> m_event_queue;
    std::jthread m_audio_handler;
    std::mutex m_audio_mutex;
    std::condition_variable m_any_audio_requests;
    bool m_quiting_audio{};
};

SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl::SoundSystemSDL3_MixerImpl()
{
    if (!Mix_OpenAudio(0, nullptr))
    {
        std::cerr << "failed loading audio " << SDL_GetError() << '\n';
    }

    m_audio_handler = std::jthread(&SoundSystemSDL3_MixerImpl::audio_processor, this);
}

SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl::~SoundSystemSDL3_MixerImpl()
{
    std::unique_lock lock(m_audio_mutex);
    m_quiting_audio = true;
    m_any_audio_requests.notify_all();
}

void SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl::play(const std::string& song_path, const float volume)
{
    m_event_queue.push(AudioEvent{song_path, volume});
    m_any_audio_requests.notify_one();
}

void SoundSystemSDL3_Mixer::SoundSystemSDL3_MixerImpl::audio_processor()
{
    while (!m_quiting_audio)
    {
        std::unique_lock lock(m_audio_mutex);
        m_any_audio_requests.wait(lock, [this] { return !m_event_queue.empty() || m_quiting_audio; });
        if (m_event_queue.empty())
            continue;

        AudioEvent& event = m_event_queue.front();

        if (!m_loaded_audio.contains(event.sound_path))
        {
            m_loaded_audio[event.sound_path] = Mix_LoadWAV(event.sound_path.c_str());
        }

        Mix_VolumeChunk(m_loaded_audio[event.sound_path], static_cast<int>(event.volume * MIX_MAX_VOLUME));
        Mix_PlayChannel(-1, m_loaded_audio[event.sound_path], 0);

        m_event_queue.pop();
    }
}


// PUBLIC INTERFACE

SoundSystemSDL3_Mixer::SoundSystemSDL3_Mixer() : m_handler{std::make_unique<SoundSystemSDL3_MixerImpl>()}
{
}

SoundSystemSDL3_Mixer::~SoundSystemSDL3_Mixer() = default;

void SoundSystemSDL3_Mixer::play(const std::string& song_path, float volume)
{
    m_handler->play(song_path, volume);
}

