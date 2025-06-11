#pragma once
#include <string>

#include <Component/Component.h>
#include "SDL3/SDL_render.h"
#include "Transform.h"

namespace stump
{
    class Texture2D final : public Component
    {
    public:
        explicit Texture2D(GameObject& attached_game_object, const std::string& path);

        Texture2D& draw_center(bool is_center);
        Texture2D& draw_size(float multipliction);

    private:
        void render(SDL_Renderer* renderer) override;

        SDL_Texture* m_texture{};
        Transform*   m_transform;
        bool         m_draw_center{ false };
        float        m_size_mulitplire{ 1 };
    };
} // namespace stump