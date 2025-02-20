#include "TextDisplay.h"

#include "GameObject.h"
#include "Minigin.h"
#include "Transform.h"

TextDisplay::TextDisplay(GameObject& game_object, const std::string& font, std::string_view text, const float size):
	Component(game_object),
	m_font(TTF_OpenFont(font.c_str(), size)),
	m_font_size(size), m_text(std::move(text)),
	m_transform(get_game_object().get_component<Transform>())
{
	update_text(text);
}

void TextDisplay::update_text(const std::string_view text)
{
	SDL_DestroyTexture(m_text_texture);

	constexpr SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.data(), text.size(), color);
	m_text_texture = SDL_CreateTextureFromSurface(get_game_object().get_engine().get_renderer(), surface);
	SDL_DestroySurface(surface);
}

void TextDisplay::render()
{
	const glm::vec2& pos = m_transform->get_world_position();

	const SDL_FRect dest_location{
		pos.x, pos.y, static_cast<float>(m_text_texture->w),
		static_cast<float>(m_text_texture->h)
	};
	SDL_RenderTexture(get_game_object().get_engine().get_renderer(), m_text_texture, nullptr, &dest_location);
}
