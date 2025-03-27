#pragma once
#include <string>

#include <Component/Component.h>
#include "Transform.h"
#include "SDL3/SDL_render.h"

class Texture2D final : public Component
{
public:
	explicit Texture2D(GameObject& attached_game_object, std::string path);
	~Texture2D() override;


	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D operator=(const Texture2D&) = delete;
	Texture2D operator=(Texture2D&&) = delete;

private:
	void render() override;

	SDL_Texture* m_texture{};
	Transform* m_transform;
	std::string m_texture_path;
};
