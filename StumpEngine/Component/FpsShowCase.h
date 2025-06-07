#pragma once
#include <chrono>
#include <Component/Component.h>

namespace stump
{
    class TextDisplay;

    class FpsShowcase final : public Component
    {
    public:
        explicit FpsShowcase(GameObject& attached_game_object);
        ~FpsShowcase() override = default;

        FpsShowcase(const FpsShowcase& other) = delete;
        FpsShowcase(FpsShowcase&& other) = delete;
        FpsShowcase& operator=(const FpsShowcase& other) = delete;
        FpsShowcase& operator=(FpsShowcase&& other) = delete;

    private:
        void         update() override;
        TextDisplay* m_text_display;

        std::chrono::time_point<std::chrono::steady_clock> m_previous;
    };
} // namespace stump
