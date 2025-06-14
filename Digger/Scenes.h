#pragma once
#include "Components/ModeSelectUI.h"

#include <Scene.h>
#include <memory>

namespace stump
{
    class StumpEngine;
} // namespace stump

namespace Scenes
{
    std::unique_ptr<stump::Scene> level_scene(stump::StumpEngine& engine, GameModes mode, const std::string& level);
    std::unique_ptr<stump::Scene> ui_scene(stump::StumpEngine& engine);
}; // namespace Scenes
