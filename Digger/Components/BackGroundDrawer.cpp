#include "BackGroundDrawer.h"

#include <GameObject.h>
#include <StumpEngine.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

struct colors
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

BackGroundDrawer::BackGroundDrawer(GameObject& attached_game_object) : Component{attached_game_object}
{
    //TODO: switch to SDL_PIXELFORMAT_RGB24
    m_texture = SDL_CreateTexture(get_game_object().get_engine().get_renderer(), SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 960 / 3, 600 / 3); // TODO: screen size
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    colors* pixel_data{};
    int pitch{};
    SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(&pixel_data), &pitch);

    for (int i = 0; i < m_texture->w * m_texture->h; ++i)
    {
        float fx = 1.6f;
        // how much to displace columns vertically
        float fy = 1.0f;
        float amp = 1.0f; // in pixels

        int x = i % m_texture->w;
        int y = i / m_texture->w;

        float rowOffset = std::sin(x * fy) * amp;

        float wave = std::sin((y + rowOffset) * fx);
        float intensity = wave * 0.5f + 0.5f;

        colors what = intensity > 0.5f ? colors{204, 0, 0} : colors{204, 116, 0};

        pixel_data[i] = what;
    }
    SDL_UnlockTexture(m_texture);
}

void BackGroundDrawer::render()
{
    SDL_FRect dst{0, 0, 960, 600};
    SDL_RenderTexture(get_game_object().get_engine().get_renderer(), m_texture, nullptr, &dst);
}

void BackGroundDrawer::update()
{
    // float x{};
    // float y{};
    // SDL_MouseButtonFlags flags = SDL_GetMouseState(&x, &y);

    // x = x / 3;
    // y = y / 3;

    // if (SDL_BUTTON_LMASK == flags)
    // {
    //     colors* pixel_data{};
    //     int pitch{};
    //     SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(&pixel_data), &pitch);
    //
    //     pixel_data[(static_cast<int>(x) + static_cast<int>(y) * m_texture->w)].r = 0u;
    //
    //     SDL_UnlockTexture(m_texture);
    // }
}

void BackGroundDrawer::delete_on_texture(const SDL_Rect& rect)
{
    SDL_Rect copy = rect;
    copy.x = copy.x / 3;
    copy.y = copy.y / 3;
    copy.w = copy.w / 3;
    copy.h = copy.h / 3;

    colors* pixel_data{};
    int pitch{};
    SDL_LockTexture(m_texture, &copy, reinterpret_cast<void**>(&pixel_data), &pitch);

    for (int i = 0; i < copy.w * copy.h; ++i)
    {
        pixel_data[i] = colors{0, 0, 0};
    }

    // pixel_data[(static_cast<int>(x) + static_cast<int>(y) * m_texture->w)].r = 0u;

    SDL_UnlockTexture(m_texture);
}
