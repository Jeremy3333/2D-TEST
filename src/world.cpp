#include "World.hpp"
#include <random>
#include <iostream>

World::World()
{
    srand(time(NULL));
    for (int i = 0; i < CELL_NUMBER; i++)
    {
        cells.push_back(Cell(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT), Color(rand() % 255, rand() % 255, rand() % 255, 225), CELL_SPEED, 20, CELL_SIZE + ((rand() % 10) - 5)));
    }
    for (int i = 0; i < FOOD_NUMBER; i++)
    {
        foods.push_back(Food(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
    }
    meanRadius = 0;
    meanSpeed = 0;
    TimerFood = 0;
}

World::~World()
{
    cells.clear();
}

void World::Update(float dt)
{
    meanRadius = 0;
    meanSpeed = 0;
    TimerFood += dt;
    Vec2f NewFoodPos = Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
    bool NewFood = true;
    for (int i = 0; i < cells.size(); i++)
    {
        float dist = distance(cells[i].getPos(), foods[0].getPos());
        int index = 0;
        for (int j = 1; j < foods.size(); j++)
        {
            if (distance(cells[i].getPos(), foods[j].getPos()) < dist)
            {
                dist = distance(cells[i].getPos(), foods[j].getPos());
                index = j;
            }
        }
        cells[i].update(dt, foods[index].getPos(), cells, foods, i);
        if (cells[i].getEnergy() <= 0)
        {
            cells.erase(cells.begin() + i);
        }
        meanRadius += cells[i].getRadius();
        meanSpeed += cells[i].getSpeed();
        if (distance(cells[i].getPos(), NewFoodPos) < cells[i].getRadius())
        {
            NewFood = false;
        }
    }
    meanRadius /= cells.size();
    meanSpeed /= cells.size();
    if (TimerFood > 1 && NewFood)
    {
        TimerFood = 0;
        if ((rand() % 100 < FOOD_SPAWN_RATE))
            foods.push_back(Food(NewFoodPos));
    }
    if (cells.size() == 0)
    {
        foods.clear();
        for (int i = 0; i < CELL_NUMBER; i++)
        {
            cells.push_back(Cell(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT), Color(rand() % 255, rand() % 255, rand() % 255, 225), CELL_SPEED, 20, CELL_SIZE + ((rand() % 10) - 5)));
        }
        for (int i = 0; i < FOOD_NUMBER; i++)
        {
            foods.push_back(Food(Vec2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
        }
        std::cout << "Reload" << std::endl;
    }
}