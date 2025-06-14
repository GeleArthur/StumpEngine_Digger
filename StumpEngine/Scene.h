#pragma once
#include "GameObject.h"
#include <memory>
#include <vector>

namespace stump
{
    class StumpEngine;
    class Scene final
    {
    public:
        explicit Scene(StumpEngine& engine);
        ~Scene();

        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene operator=(const Scene&) = delete;
        Scene operator=(Scene&&) = delete;

        void cleanup();
        void fixed_update() const;
        void update() const;
        void render() const;
        void delete_marked_game_objects();

        GameObject&  add_game_object();
        StumpEngine& get_engine() const;

        [[nodiscard]] const std::vector<std::unique_ptr<GameObject>>& get_all_game_objects()
        {
            return m_game_objects;
        }

    private:
        std::vector<std::unique_ptr<GameObject>> m_game_objects{};
        std::vector<std::unique_ptr<GameObject>> m_game_objects_to_be_added{};
        StumpEngine*                             m_engine;
    };
} // namespace stump
