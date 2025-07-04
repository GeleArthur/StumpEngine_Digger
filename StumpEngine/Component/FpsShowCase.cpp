#include "FpsShowCase.h"

#include <GameObject.h>
#include <StumpEngine.h>
#include <Component/TextDisplay.h>

stump::FpsShowcase::FpsShowcase(GameObject& attached_game_object)
    : Component(attached_game_object)
    , m_text_display(get_game_object().get_component<TextDisplay>())
{
}

void stump::FpsShowcase::update()
{
    const float fps = 1.0f / EngineTime::instance().get_delta_time();

    std::stringstream out;
    out << std::fixed;
    out << std::setprecision(1);
    out << fps;
    out << " :FPS";

    m_text_display->update_text(out.str());
    ;
}
