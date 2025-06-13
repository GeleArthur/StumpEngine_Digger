#pragma once
#include "DirtGrid.h"
#include "GridTransform.h"

#include <Event.h>
#include <EventListener.h>
#include <vector>
#include <Component/Component.h>

struct Cell
{
    float      cost;
    glm::ivec2 direction;
};

class Digger;
class GameDataTracker : public stump::Component
{
public:
    explicit GameDataTracker(stump::GameObject& attached, DirtGrid& grid);
    void add_player(GridTransform& digger)
    {
        m_players.push_back(&digger);
    }
    void remove_player(const GridTransform& digger)
    {
        m_players.erase(std::find(m_players.begin(), m_players.end(), &digger));
    }

    using FlowField = std::array<Cell, GridSettings::grid_tile_count.y * GridSettings::grid_tile_count.x>;

    const FlowField& get_flow_field() const
    {
        return m_flow_field;
    }

    void update() override;
    void update_flow_field();

private:
    FlowField                   m_flow_field{};
    std::vector<GridTransform*> m_players;
    DirtGrid*                   m_grid;
};
