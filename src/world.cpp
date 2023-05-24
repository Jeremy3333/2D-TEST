#include "World.hpp"

World::World()
{
    cells.push_back(Cell(Vec2f(100, 90), 10, 100));
    cells.push_back(Cell(Vec2f(60, 100), 10, 100));
}

World::~World()
{
    cells.clear();
}

void World::Update(float dt)
{
    for(int i = 0; i < cells.size(); i++)
    {
        cells[i].update(dt, Vec2f(0, 0), cells);
    }
}