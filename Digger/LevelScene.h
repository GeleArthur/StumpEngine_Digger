#pragma once
#include <memory>

namespace stump
{
    class Scene;
    class StumpEngine;
} // namespace stump

namespace Scenes
{
    std::unique_ptr<stump::Scene> level_scene(stump::StumpEngine& engine);
};
