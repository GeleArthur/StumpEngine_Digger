#pragma once
#include <functional>
#include <memory>

#include "EngineTime.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"

#include <Scene.h>
#include <vec2.hpp>

namespace stump
{
    class IRenderable;
    class GameObject;

    class StumpEngine final
    {
    public:
        explicit StumpEngine(const std::function<void(StumpEngine&)>& function);
        ~StumpEngine();

        StumpEngine(const StumpEngine&) = delete;
        StumpEngine(StumpEngine&&) = delete;
        StumpEngine operator=(const StumpEngine&) = delete;
        StumpEngine operator=(StumpEngine&&) = delete;

        [[nodiscard]] SDL_Renderer* get_renderer() const;
        void                        set_window_size(int width, int height);
        const glm::ivec2&           get_window_size() const;
        void                        set_active_scene(std::unique_ptr<Scene>&& scene);

        void run();

    private:
        void handle_input();
        void run_one_loop();

        double                 m_refresh_rate_delay{};
        SDL_Window*            m_window{};
        SDL_Renderer*          m_renderer{};
        std::unique_ptr<Scene> m_scene{};
        std::unique_ptr<Scene> m_new_scene{};

        std::chrono::duration<float>                   m_time_passed{};
        const std::chrono::duration<float, std::milli> m_fixed_update_time = std::chrono::duration<float, std::milli>(45.0f);

        bool       m_is_quitting{ false };
        glm::ivec2 m_window_size{ 900, 600 };
    };

} // namespace stump
