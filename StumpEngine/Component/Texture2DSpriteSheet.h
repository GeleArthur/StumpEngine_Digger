#pragma once
#include "Texture2D.h"

namespace stump
{
    class Texture2DSpriteSheet final : public Component
    {
    public:
        explicit Texture2DSpriteSheet(GameObject& attached_game_object, const std::string& path);
        void                  render(SDL_Renderer* renderer) override;
        Texture2DSpriteSheet& set_sprite_size(const glm::ivec2 size)
        {
            m_sprite_size = size;
            return *this;
        };

        Texture2DSpriteSheet& set_sprite_index(const glm::ivec2 index)
        {
            m_sprite_index = index;
            return *this;
        }

        Texture2DSpriteSheet& set_size_multiplier(const float size)
        {
            m_size_multiplier = size;
            return *this;
        }

    private:
        glm::ivec2   m_sprite_index{};
        glm::ivec2   m_sprite_size{};
        SDL_Texture* m_texture;
        Transform*   m_transform;
        float        m_size_multiplier{ 1 };
    };
} // namespace stump
