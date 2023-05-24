#include "World.hpp"

World::World()
{
    cells.push_back(Cell(Vec2f(100, 90), 30, 100, CELL_SIZE));
    cells.push_back(Cell(Vec2f(60, 100), 30, 100, CELL_SIZE));
}

World::~World()
{
    cells.clear();
}

void World::Update(float dt)
{
    for(int i = 0; i < cells.size(); i++)
    {
        cells[i].update(dt, Vec2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), cells, i);
    }
}