#include "Texture2D.h"

#include <utility>

#include <GameObject.h>
#include <StumpEngine.h>
#include "SDL3_image/SDL_image.h"
#include "Transform.h"

Texture2D::Texture2D(GameObject& attached_game_object, std::string path)
    : Component(attached_game_object)
    , m_transform(get_game_object().get_component<Transform>())
    , m_texture_path(std::move(path))
{
    // TODO: resource manager
    m_texture = IMG_LoadTexture(get_game_object().get_engine().get_renderer(), m_texture_path.c_str());
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
}

Texture2D::~Texture2D()
{
    SDL_DestroyTexture(m_texture);
}

Texture2D& Texture2D::draw_center(bool is_center)
{
    m_draw_center = is_center;
    return *this;
}
Texture2D& Texture2D::draw_size(float multipliction)
{
    m_size_mulitplire = multipliction;
    return *this;
}
void Texture2D::render(SDL_Renderer* renderer)
{
    const glm::vec2& pos = m_transform->get_world_position();

    SDL_FRect dest_location{};
    if (m_draw_center)
    {
        dest_location = SDL_FRect{ pos.x - static_cast<float>((m_texture->w / 2)) * m_size_mulitplire, pos.y - static_cast<float>(m_texture->h / 2) * m_size_mulitplire, static_cast<float>(m_texture->w) * m_size_mulitplire, static_cast<float>(m_texture->h) * m_size_mulitplire };
    }
    else
    {
        dest_location = SDL_FRect{ pos.x, pos.y, static_cast<float>(m_texture->w * m_size_mulitplire), static_cast<float>(m_texture->h * m_size_mulitplire) };
    }
    SDL_RenderTexture(renderer, m_texture, nullptr, &dest_location);
}
