#include "World.hpp"
#include <random>

World::World()
{
    srand(time(NULL));
    for(int i = 0; i < 3; i++)
    {
        cells.push_back(Cell(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT), 10, 10, ((rand() % 2) + 1) * CELL_SIZE));
    }
    for(int i = 0; i < 10; i++)
    {
        foods.push_back(Food(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
    }
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