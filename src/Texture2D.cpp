#include "Texture2D.h"

#include "GameObject.h"
#include "Minigin.h"
#include "SDL3_image/SDL_image.h"

Texture2D::Texture2D(GameObject* attached_game_object, const std::string& path): Component(attached_game_object), m_texturePath(path)
{
	m_texture = IMG_LoadTexture(AttachedGameObject->get_engine()->get_renderer(), m_texturePath.c_str());
}



Texture2D::~Texture2D()
{
}
