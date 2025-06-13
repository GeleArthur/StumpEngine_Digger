#include "ResourceManager.h"

#include <ranges>
#include <SDL3_image/SDL_image.h>
ResourceManager::~ResourceManager()
{
    for (const auto& texture : m_cached_textures | std::views::values)
    {
        SDL_DestroyTexture(texture);
    }

    for (const auto& font : m_cached_font | std::views::values)
    {
        TTF_CloseFont(font);
    }

    for (const auto& texture : m_cached_text | std::views::values)
    {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* ResourceManager::get_texture(const std::string& texture_path)
{
    if (m_cached_textures.contains(texture_path))
    {
        return m_cached_textures[texture_path];
    }

    m_cached_textures[texture_path] = IMG_LoadTexture(m_renderer, texture_path.c_str());
    return m_cached_textures[texture_path];
}
SDL_Texture* ResourceManager::get_text(const std::string& font, const std::string& text, float size, SDL_Color color)
{
    const auto font_key = std::pair{ font, size };

    if (!m_cached_font.contains(font_key))
    {
        m_cached_font[font_key] = TTF_OpenFont(font.c_str(), size);
    }

    const auto text_key = std::pair{ text, color };

    if (!m_cached_text.contains(text_key))
    {
        SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(m_cached_font[font_key], text.data(), text.size(), color, 0);

        m_cached_text[text_key] = SDL_CreateTextureFromSurface(m_renderer, surface);

        SDL_DestroySurface(surface);
    }

    return m_cached_text[text_key];
}