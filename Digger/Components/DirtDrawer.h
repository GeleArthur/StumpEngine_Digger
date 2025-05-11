#pragma once
#include <Component/Component.h>
#include <SDL3/SDL_render.h>

class DirtDrawer final : public Component
{
public:
    explicit DirtDrawer(GameObject& attached_game_object);
    void render(SDL_Renderer* renderer) override;
    void update() override;

    void delete_on_texture(const SDL_Rect& rect) const;

private:
    SDL_Texture* m_texture{};
};
