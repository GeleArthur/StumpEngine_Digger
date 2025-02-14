#pragma once
#include <string>

#include "component.h"
#include "SDL3/SDL_render.h"

class Texture2D final : public Component
{
public:
	explicit Texture2D(GameObject* attached_game_object, const std::string& path);
	~Texture2D() override;


	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D operator=(const Texture2D&) = delete;
	Texture2D operator=(Texture2D&&) = delete;

private:
	SDL_Texture* m_texture{};
	std::string m_texturePath;
};
