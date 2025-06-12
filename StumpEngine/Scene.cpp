#include "Scene.h"

#include <GameObject.h>
#include <StumpEngine.h>

namespace stump
{

    Scene::Scene(StumpEngine& engine)
        : m_engine{ &engine }
    {
    }
    Scene::~Scene()
    {
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->mark_for_deletion();
        }
        delete_marked_game_objects();
    }
    void Scene::fixed_update() const
    {
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->fixed_update();
        }
    }
    void Scene::update() const
    {
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->update();
        }
    }
    void Scene::render() const
    {
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->render(m_engine->get_renderer());
        }
    }
    GameObject& Scene::add_game_object()
    {
        m_game_objects.push_back(std::make_unique<GameObject>(*m_engine));
        return *m_game_objects[m_game_objects.size() - 1];
    }
    void Scene::delete_marked_game_objects()
    {
        for (const std::unique_ptr<GameObject>& game_object : m_game_objects)
        {
            game_object->removed_marked_components();
        }

        std::erase_if(m_game_objects, [](const std::unique_ptr<GameObject>& game_object) { return game_object->is_marked_for_deletion(); });
    }
} // namespace stump