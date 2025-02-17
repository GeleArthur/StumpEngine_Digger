#include "Texture2D.h"

#include "GameObject.h"
#include "Minigin.h"
#include "Transform.h"
#include "SDL3_image/SDL_image.h"

Texture2D::Texture2D(GameObject& attached_game_object, const std::string& path): Component(attached_game_object),
                                                                                 m_texture_path(path)
{
	m_texture = IMG_LoadTexture(GetGameObject()->get_engine()->get_renderer(), m_texture_path.c_str());
}


Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

void Texture2D::render()
{
	Transform* pos = GetGameObject()->get_component<Transform>();

	const SDL_FRect dest_location{
		pos->m_position.x, pos->m_position.y, static_cast<float>(m_texture->w), static_cast<float>(m_texture->h)
	};
	SDL_RenderTexture(GetGameObject()->get_engine()->get_renderer(), m_texture, nullptr, &dest_location);
}
