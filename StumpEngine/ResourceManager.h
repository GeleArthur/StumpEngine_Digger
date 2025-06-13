#pragma once
#include <unordered_map>
#include <Singleton.h>
#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

struct HashFont
{
    std::size_t operator()(const std::pair<std::string, float>& key) const
    {
        std::hash<std::string> str_hash;
        std::hash<float>       int_hash;
        return str_hash(key.first) ^ (int_hash(key.second) << 1);
    }
};

inline bool operator==(const SDL_Color& lhs, const SDL_Color& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

struct HashColor
{
    std::size_t operator()(const SDL_Color& color) const
    {
        return static_cast<std::size_t>(color.r) |
            (static_cast<std::size_t>(color.g) << 8) |
            (static_cast<std::size_t>(color.b) << 16) |
            (static_cast<std::size_t>(color.a) << 24);
    }
};

struct HashText
{
    std::size_t operator()(const std::pair<std::string, SDL_Color>& key) const
    {
        std::hash<std::string> str_hash;
        HashColor              color_hash;
        return str_hash(key.first) ^ (color_hash(key.second) << 1);
    }
};

// TODO: Make it a serverse locator
// TODO: cleanup textures when not used
class ResourceManager final : public Singleton<ResourceManager>
{
public:
    ~ResourceManager();
    void set_renderer(SDL_Renderer* renderer)
    {
        m_renderer = renderer;
    }

    SDL_Texture* get_texture(const std::string& texture_path);
    SDL_Texture* get_text(const std::string& font, const std::string& text = "", float size = 16.0f, SDL_Color color = { 255, 255, 255, 255 });

private:
    friend Singleton;
    explicit ResourceManager() = default;
    // TODO: Use compile time texture ID
    SDL_Renderer*                                                                 m_renderer;
    std::unordered_map<std::string, SDL_Texture*>                                 m_cached_textures;
    std::unordered_map<std::pair<std::string, float>, TTF_Font*, HashFont>        m_cached_font;
    std::unordered_map<std::pair<std::string, SDL_Color>, SDL_Texture*, HashText> m_cached_text;
};
