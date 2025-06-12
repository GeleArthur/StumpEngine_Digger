#include "Texture2DSpriteSheet.h"
#include <GameObject.h>
#include <ResourceManager.h>

stump::Texture2DSpriteSheet::Texture2DSpriteSheet(GameObject& attached_game_object, const std::string& path)
    : Component{ attached_game_object }
    , m_texture{ ResourceManager::instance().get_texture(path) }
    , m_transform(get_game_object().get_component<Transform>())
{
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
}

void stump::Texture2DSpriteSheet::render(SDL_Renderer* renderer)
{
    const glm::vec2& pos = m_transform->get_world_position();

    SDL_FRect src_location{
        static_cast<float>(m_sprite_index.x * m_sprite_size.x),
        static_cast<float>(m_sprite_index.y * m_sprite_size.y),
        static_cast<float>(m_sprite_size.x),
        static_cast<float>(m_sprite_size.y),
    };

    SDL_FRect dest_location{
        pos.x - m_sprite_size.x / 2.0f * m_size_multiplier,
        pos.y - m_sprite_size.y / 2.0f * m_size_multiplier,
        static_cast<float>(m_sprite_size.x) * m_size_multiplier,
        static_cast<float>(m_sprite_size.y) * m_size_multiplier
    };

    // SDL_RenderTexture(renderer, m_texture, &src_location, &dest_location);
    SDL_RenderTextureRotated(renderer, m_texture, &src_location, &dest_location, m_rotation, nullptr, m_flip_mode);

    // SDL_RenderRect(renderer, &dest_location);
}
