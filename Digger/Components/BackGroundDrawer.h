#pragma once
#include <Component/Component.h>
#include <SDL3/SDL_render.h>

class BackGroundDrawer final : public Component
{
public:
    explicit BackGroundDrawer(GameObject& attached_game_object);
    void render() override;
    void update() override;

    void delete_on_texture(const SDL_Rect& rect);

private:
    SDL_Texture* m_texture{};
};

