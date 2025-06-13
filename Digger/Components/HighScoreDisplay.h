#pragma once
#include <Component/Component.h>

namespace stump
{
    class Scene;
}
class HighScoreDisplay final : public stump::Component
{
public:
    explicit HighScoreDisplay(stump::GameObject& attached, stump::Scene& scene);

private:
};
