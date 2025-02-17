#include "TextDisplay.h"

#include "GameObject.h"
#include "Minigin.h"
#include "Transform.h"

TextDisplay::TextDisplay(GameObject& game_object, const std::string& font, std::string_view text, const float size):
	Component(game_object),
	m_font_size(size),
	m_text(std::move(text))
{
	m_font = TTF_OpenFont(font.c_str(), size);
	update_text(text);
}

void TextDisplay::update_text(const std::string_view text)
{
	SDL_DestroyTexture(m_text_texture);

	const SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.data(), text.size(), color);
	m_text_texture = SDL_CreateTextureFromSurface(GetGameObject()->get_engine()->get_renderer(), surface);
	SDL_DestroySurface(surface);
}

void TextDisplay::render()
{
	const Transform* pos = GetGameObject()->get_component<Transform>();

	const SDL_FRect dest_location{
		pos->m_position.x, pos->m_position.y, static_cast<float>(m_text_texture->w),
		static_cast<float>(m_text_texture->h)
	};
	SDL_RenderTexture(GetGameObject()->get_engine()->get_renderer(), m_text_texture, nullptr, &dest_location);
}
