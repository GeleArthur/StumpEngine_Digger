#include "TextDisplay.h"

#include "../GameObject.h"
#include "../StumpEngine.h"
#include "Transform.h"

stump::TextDisplay::TextDisplay(GameObject& game_object, const std::string& font, std::string_view text, const float size)
    : Component(game_object)
    , m_font(TTF_OpenFont(font.c_str(), size))
    , m_font_size(size)
    , m_text(std::move(text))
    , m_transform(get_game_object().get_transform())
{
    update_text(text);
}

stump::TextDisplay::~TextDisplay()
{
    TTF_CloseFont(m_font);
    SDL_DestroyTexture(m_text_texture);
}

void stump::TextDisplay::update_text(const std::string_view text)
{
    SDL_DestroyTexture(m_text_texture);

    constexpr SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface*        surface = TTF_RenderText_Blended_Wrapped(m_font, text.data(), text.size(), color, 0);
    // TODO: Resource manager
    m_text_texture = SDL_CreateTextureFromSurface(get_game_object().get_engine().get_renderer(), surface);
    SDL_DestroySurface(surface);
}

void stump::TextDisplay::render(SDL_Renderer* renderer)
{
    const glm::vec2& pos = m_transform.get_world_position();

    const SDL_FRect dest_location{ pos.x, pos.y, static_cast<float>(m_text_texture->w), static_cast<float>(m_text_texture->h) };
    SDL_RenderTexture(renderer, m_text_texture, nullptr, &dest_location);
}
