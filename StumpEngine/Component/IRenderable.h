#pragma once
#include <SDL3/SDL_render.h>
#include <concepts>
namespace stump
{
    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;

        IRenderable(const IRenderable& other) = delete;
        IRenderable(IRenderable&& other) = delete;
        IRenderable& operator=(const IRenderable& other) = delete;
        IRenderable& operator=(IRenderable&& other) = delete;

        virtual void render(SDL_Renderer renderer) = 0;
    };

    template<typename NewComponent>
    concept is_renderable = std::derived_from<NewComponent, IRenderable>;
} // namespace stump