#include "Cell.hpp"
#include <iostream>

void Cell::collide(Cell& other)
{
    int totalRadius = radius + other.radius;
    Vec2f otherPos = other.getPos();
    Vec2f dist = position - otherPos;
    if (distance(position, otherPos) < totalRadius)
    {
        Vec2f temp(position.x, position.y);
        driveAway(position, otherPos, totalRadius-distance(position, otherPos), ((float)radius)/((float)totalRadius));
    }
}

Cell::Cell(Vec2f position, float speed, int energy, int radius): position(position), speed(speed), Timer(0), energy(energy), radius(radius) {}

Cell::~Cell() {}

Vec2f Cell::getPos() const
{
    return position;
}

void Cell::setPos(const Vec2f& position)
{
    this->position = position;
}

int Cell::getSpeed() const
{
    return speed;
}

int Cell::getEnergy() const
{
    return energy;
}

int Cell::getRadius() const
{
    return radius;
}

void Cell::update(float dt, Vec2f target, std::vector<Cell> &cells, std::vector<Food> &foods, int id)
{
    position = position + normalize(target - position) * speed * dt;
    Timer += dt;
    for(int i = 0; i < cells.size(); i++)
    {
        if(i != id)
        {
            collide(cells[i]);
        }
    }
    for(int i = 0; i < foods.size(); i++)
    {
        if(distance(position, foods[i].getPos()) < radius + FOOD_SIZE)
        {
            energy += FOOD_ENERGY;
            foods.erase(foods.begin() + i);
        }
    }
    if(Timer >= 1)
    {
        energy -= (speed/CELL_SPEED)*(CELL_SPEED_ENERGY_COST)+(radius/CELL_SIZE)*(CELL_SIZE_ENERGY_COST);
        Timer = 0;
    }
    if(energy >= CHILDBIRTH_ENERGY)
    {
        energy -= BIRTH_ENERGY;
        int childSpeed = this->speed;
        int childRadius = this->radius;
        int childX = position.x + ((rand() % 10) - 5);
        int childY = position.y + ((rand() % 10) - 5);
        if(rand() % 100 < MUTATION_CHANCE)
        {
            childSpeed += ((rand() % 10) - 5);
        }
        if(rand() % 100 < MUTATION_CHANCE)
        {
            childRadius += ((rand() % 10) - 5);
        }
        cells.push_back(Cell(Vec2f(childX, childY), childSpeed, BIRTH_ENERGY, childRadius));
    }
}