#include "Cell.hpp"
#include <iostream>

Cell::Cell(): position(Vec2f(0, 0)), speed(0), Timer(0), energy(0) {}

Cell::Cell(Vec2f position, float speed, int energy): position(position), speed(speed), Timer(0), energy(energy) {}

Cell::~Cell() {}

Vec2f Cell::getPos() const
{
    return position;
}

void Cell::setPos(const Vec2f& position)
{
    this->position = position;
}

void Cell::update(float dt, Vec2f target, std::vector<Cell> cells)
{
    position = position + normalize(target - position) * speed * dt;
    for(int i = 0; i < cells.size(); i++)
    {
        Vec2f BPos = cells[i].getPos();
        if(distance(position, BPos) < CELL_SIZE * 2 && position != BPos)
        {
            driveAway(position, BPos, distance(position, BPos));
            cells[i].setPos(BPos);
        }
    }
}