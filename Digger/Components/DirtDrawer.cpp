#include "DirtDrawer.h"

#include <GameObject.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <StumpEngine.h>

struct colors
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

DirtDrawer::DirtDrawer(stump::GameObject& attached_game_object)
    : Component{ attached_game_object }
{
    // TODO: screen size
    m_texture = SDL_CreateTexture(get_game_object().get_engine().get_renderer(), SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 320, 200);
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    colors* pixel_data{};
    int     pitch{};
    SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(&pixel_data), &pitch);

    for (int i = 0; i < m_texture->w * m_texture->h; ++i)
    {
        // TODO: Wrong need to reworked as red and orange lines are not equal
        const int x = i % m_texture->w;
        const int y = i / m_texture->w;
        const int period = 6;

        const int stripe = y / period;
        const int y_in_stripe = y % period;

        const int   amplutide = 3;
        const float wave = amplutide + (std::sin(static_cast<float>(x * 0.4)) * amplutide);

        const bool above = y_in_stripe > wave;

        const bool use_first_color = above ^ (stripe & 1);

        const colors what = use_first_color ? colors{ 204, 0, 0 } : colors{ 204, 116, 0 };

        pixel_data[i] = what;
    }
    SDL_UnlockTexture(m_texture);
}

void DirtDrawer::render(SDL_Renderer* renderer)
{
    const SDL_FRect dst{ 0, 0, 960, 600 };
    SDL_RenderTexture(renderer, m_texture, nullptr, &dst);
}

void DirtDrawer::update() {}

void DirtDrawer::delete_on_texture(const SDL_Rect& rect) const
{
    colors* pixel_data{};
    int     pitch{};
    SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(&pixel_data), &pitch);

    const std::span mapped_data(pixel_data, m_texture->w * m_texture->h);
    for (int i = 0; i < rect.w * rect.h; ++i)
    {
        mapped_data[rect.x / 3 + rect.y / 3 * m_texture->w + (i % rect.w) + ((i / rect.w) * m_texture->w)] =
            colors{ 0, 0, 0 };
    }

    SDL_UnlockTexture(m_texture);
}
