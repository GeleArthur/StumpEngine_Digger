#include "Texture2D.h"

#include <utility>

#include "Transform.h"
#include "SDL3_image/SDL_image.h"
#include <GameObject.h>
#include <ResourceManager.h>
#include <StumpEngine.h>
namespace stump
{
    Texture2D::Texture2D(GameObject& attached_game_object, const std::string& path)
        : Component(attached_game_object)
        , m_transform(get_game_object().get_component<Transform>())
    {
        m_texture = ResourceManager::instance().get_texture(path);
        SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
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
            dest_location = SDL_FRect{ pos.x - m_texture->w / 2.0f * m_size_mulitplire, pos.y - m_texture->h / 2.0f * m_size_mulitplire, static_cast<float>(m_texture->w) * m_size_mulitplire, static_cast<float>(m_texture->h) * m_size_mulitplire };
        }
        else
        {
            dest_location = SDL_FRect{ pos.x, pos.y, (m_texture->w * m_size_mulitplire), (m_texture->h * m_size_mulitplire) };
        }
        SDL_RenderTexture(renderer, m_texture, nullptr, &dest_location);
    }
} // namespace stump