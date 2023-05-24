#pragma once
#include "Vec2f.hpp"
#include "Utils.hpp"
#include <vector>

class Cell
{
private:
    Vec2f position;
    float speed;
    float Timer;
    int energy;
    int radius;
    void collide(Cell& other);

public:
    Cell(Vec2f position, float speed, int energy, int radius);

    Vec2f getPos() const;
    void setPos(const Vec2f& position);

    int getRadius() const;

    void update(float dt, Vec2f target, std::vector<Cell> cells, int id);

    ~Cell();
};