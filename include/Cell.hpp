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

public:
    Cell();
    Cell(Vec2f position, float speed, int energy);

    Vec2f getPos() const;
    void setPos(const Vec2f& position);

    void update(float dt, Vec2f target, std::vector<Cell> cells);

    ~Cell();
};