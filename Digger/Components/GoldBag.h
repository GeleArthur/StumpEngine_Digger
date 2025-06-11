#pragma once

#include <Component/Component.h>
#include <memory>

class GoldBag;

class IGoldBagState
{
public:
    virtual ~IGoldBagState() = default;
    virtual std::unique_ptr<IGoldBagState> update(GoldBag& bag) = 0;
};

class GoldBagIdle final : public IGoldBagState
{
public:
    std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;
};

class GoldBagPushed final : public IGoldBagState
{
public:
    explicit GoldBagPushed(bool going_left);
    std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;

private:
    bool  m_going_left;
    float m_time_until_next_move{ 0 };
    int   m_move_count{ 4 };
};

class GoldBagFalling final : public IGoldBagState
{
public:
    virtual std::unique_ptr<IGoldBagState> update(GoldBag& bag) override;
};

class GoldBag final : public stump::Component
{
public:
    explicit GoldBag(stump::GameObject& attached);

    void update() override;
    void pushing(bool going_left);

    // Walls get_current_walls() const;

private:
    std::unique_ptr<IGoldBagState> m_current_state{};
    // GridWalls&                     m_walls;
};
