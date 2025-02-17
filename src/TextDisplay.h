#pragma once
#include <string>

#include "Component.h"
#include "SDL3_ttf/SDL_ttf.h"

class TextDisplay final : public Component
{
public:
	TextDisplay(GameObject& game_object, const std::string& font, std::string_view text = "", float size = 16.0f);

	void update_text(std::string_view text);

	TextDisplay(const TextDisplay&) = delete;
	TextDisplay(TextDisplay&&) = delete;
	TextDisplay operator=(const TextDisplay&) = delete;
	TextDisplay operator=(TextDisplay&&) = delete;

private:
	void render() override;

	bool m_is_dirty{false};

	TTF_Font* m_font{};
	float m_font_size;
	std::string m_text;
	SDL_Texture* m_text_texture{};
};
