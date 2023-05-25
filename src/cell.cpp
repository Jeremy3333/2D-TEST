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

int Cell::getRadius() const
{
    return radius;
}

void Cell::update(float dt, Vec2f target, std::vector<Cell> cells, int id)
{
    position = position + normalize(target - position) * speed * dt;
    for(int i = 0; i < cells.size(); i++)
    {
        if(i != id)
        {
            collide(cells[i]);
        }
    }
}