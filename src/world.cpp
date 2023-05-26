#include "World.hpp"
#include <random>

World::World()
{
    srand(time(NULL));
    for(int i = 0; i < 3; i++)
    {
        cells.push_back(Cell(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT), 30, 20,  CELL_SIZE + ((rand() % 10) - 5)));
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
    float meanRadius = 0;
    float meanSpeed = 0;
    for(int i = 0; i < cells.size(); i++)
    {
        float dist = distance(cells[i].getPos(), foods[0].getPos());
        int index = 0;
        for(int j = 1; j < foods.size(); j++)
        {
            if(distance(cells[i].getPos(), foods[j].getPos()) < dist)
            {
                dist = distance(cells[i].getPos(), foods[j].getPos());
                index = j;
            }
        }
        cells[i].update(dt, foods[index].getPos(), cells, foods, i);
        if(cells[i].getEnergy() <= 0)
        {
            cells.erase(cells.begin() + i);
        }
        meanRadius += cells[i].getRadius();
        meanSpeed += cells[i].getSpeed();
    }
    meanRadius /= cells.size();
    meanSpeed /= cells.size();
    if(foods.size() < 10)
    {
        foods.push_back(Food(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
    }
}