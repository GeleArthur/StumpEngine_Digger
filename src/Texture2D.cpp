#include "Texture2D.h"

#include <utility>

#include "GameObject.h"
#include "Minigin.h"
#include "Transform.h"
#include "SDL3_image/SDL_image.h"

Texture2D::Texture2D(GameObject& attached_game_object, std::string path):
	Component(attached_game_object),
	m_transform(get_game_object().get_component<Transform>()), m_texture_path(std::move(path))
{
	m_texture = IMG_LoadTexture(get_game_object().get_engine().get_renderer(), m_texture_path.c_str());
}


Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

void Texture2D::render()
{
	const glm::vec2& pos = m_transform->get_world_position();

	const SDL_FRect dest_location{
		pos.x, pos.y, static_cast<float>(m_texture->w), static_cast<float>(m_texture->h)
	};
	SDL_RenderTexture(get_game_object().get_engine().get_renderer(), m_texture, nullptr, &dest_location);
}
