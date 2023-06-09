#pragma once
#include "Vec2f.hpp"
#include "Utils.hpp"
#include "Food.hpp"
#include "Neural.hpp"
#include "Color.hpp"
#include <vector>

class Cell
{
private:
    Vec2f position;
    Vec2f velocity;
    Color color;
    float speed;
    float Timer;
    int energy;
    int radius;
    void collide(Cell &other);
    Neural brainMove;

public:
    Cell(Vec2f position, Color color, float speed, int energy, int radius);

    Cell(Vec2f position, Color color, float speed, int energy, int radius, const Neural &Heredity);

    Vec2f getPos() const;
    void setPos(const Vec2f &position);

    Vec2f getVelocity() const;

    Color getColor() const;

    int getSpeed() const;

    int getEnergy() const;

    int getRadius() const;

    void update(float dt, Vec2f target, std::vector<Cell> &cells, std::vector<Food> &foods, int id);

    ~Cell();
};