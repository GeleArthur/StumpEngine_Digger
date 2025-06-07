#pragma once
#include <SDL3/SDL_render.h>

namespace stump
{
    class GameObject;

    class Component
    {
    public:
        explicit Component(GameObject& attached_game_object);
        virtual ~Component() = default;

        [[nodiscard]] GameObject& get_game_object() const;

        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;

        virtual void fixed_update();
        virtual void update();
        virtual void render(SDL_Renderer* renderer);

        void               mark_for_deletion();
        [[nodiscard]] bool is_marked_for_delection() const;

    private:
        GameObject& m_attached_game_object;
        bool        m_marked_for_delection{ false };
    };
} // namespace stump