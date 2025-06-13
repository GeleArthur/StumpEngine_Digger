#include "TextDisplay.h"

#include "../GameObject.h"
#include "../StumpEngine.h"
#include "Transform.h"

#include <ResourceManager.h>

stump::TextDisplay::TextDisplay(GameObject& game_object, const std::string& font, std::string_view text, const float size, SDL_Color color)
    : Component(game_object)
    , m_font(font)
    , m_font_size(size)
    , m_text(std::move(text))
    , m_transform(get_game_object().get_transform())
    , m_color{ color }
{
    update_text(text);
}

stump::TextDisplay::~TextDisplay()
{
}

void stump::TextDisplay::update_text(const std::string_view text)
{
    m_text = text;
    m_text_texture = ResourceManager::instance().get_text(m_font, m_text, m_font_size, m_color);
}

void stump::TextDisplay::render(SDL_Renderer* renderer)
{
    const glm::vec2& pos = m_transform.get_world_position();
    const SDL_FRect  dest_location{ pos.x, pos.y, static_cast<float>(m_text_texture->w), static_cast<float>(m_text_texture->h) };
    SDL_RenderTexture(renderer, m_text_texture, nullptr, &dest_location);
}
