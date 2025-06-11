#include "ResourceManager.h"

#include <SDL3_image/SDL_image.h>
ResourceManager::~ResourceManager()
{
    for (const std::pair<const std::string, SDL_Texture*>& texture : m_chached_textures)
    {
        SDL_DestroyTexture(texture.second);
    }
}
SDL_Texture* ResourceManager::get_texture(const std::string& texture_path)
{
    if (m_chached_textures.contains(texture_path))
    {
        return m_chached_textures[texture_path];
    }

    m_chached_textures[texture_path] = IMG_LoadTexture(m_renderer, texture_path.c_str());
    return m_chached_textures[texture_path];
}