#include "FpsShowCase.h"

#include "GameObject.h"
#include "Minigin.h"
#include "TextDisplay.h"

FpsShowcase::FpsShowcase(GameObject* attached_game_object): Component(attached_game_object)
{
}

void FpsShowcase::update()
{
	const float fps = 1.0f/m_attached_game_object->get_engine()->EngineTime.DeltaTime;

	std::stringstream out;
	out << std::fixed;
	out << std::setprecision(1);
	out << fps;
	out << " :FPS";

	m_attached_game_object->get_component<TextDisplay>()->update_text(out.str());
;}
