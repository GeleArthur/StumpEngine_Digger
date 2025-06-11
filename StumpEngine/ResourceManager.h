#pragma once
#include <unordered_map>
#include <Singleton.h>
#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL_render.h>

// TODO: Make it a serverse locator
// TODO: cleanup textures when not used
class ResourceManager final : public Singleton<ResourceManager>
{
public:
    ~ResourceManager();
    void set_rendererer(SDL_Renderer* renderer)
    {
        m_renderer = renderer;
    }

    SDL_Texture* get_texture(const std::string& texture_path);

private:
    friend Singleton;
    explicit ResourceManager() = default;
    // TODO: Use compile time texture ID
    SDL_Renderer*                                 m_renderer;
    std::unordered_map<std::string, SDL_Texture*> m_chached_textures;
};
