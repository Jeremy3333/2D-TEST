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

Cell::Cell(Vec2f position, Color color, float speed, int energy, int radius): position(position), velocity(), color(color), speed(speed), Timer(0), energy(energy), radius(radius), brainMove() {}

Cell::Cell(Vec2f position, Color color, float speed, int energy, int radius, const Neural &Heredity): position(position), velocity(), color(color), speed(speed), Timer(0), energy(energy), radius(radius), brainMove(Heredity) {}

Cell::~Cell() {}

Vec2f Cell::getPos() const
{
    return position;
}

void Cell::setPos(const Vec2f& position)
{
    this->position = position;
}

Vec2f Cell::getVelocity() const
{
    return velocity;
}

Color Cell::getColor() const
{
    return color;
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
    Vec2f input = target - position;
    float input1[4] = {input.x, input.y, velocity.x, velocity.y};
    float output[2];
    brainMove.Solve(input1, output);
    if(output[0] > 0)
        velocity.x += speed * dt;
    else if(output[0] < 0)
        velocity.x -= speed * dt;
    if(output[1] > 0)
        velocity.y += speed * dt;
    else if(output[1] < 0)
        velocity.y -= speed * dt;
    velocity *= CELL_FRICTION;
    position += velocity * dt;
    if(position.x - radius < 0)
        position.x = radius;
    if(position.x + radius > WINDOW_WIDTH)
        position.x = WINDOW_WIDTH - radius;
    if(position.y - radius < 0)
        position.y = radius;
    if(position.y + radius > WINDOW_HEIGHT)
        position.y = WINDOW_HEIGHT - radius;
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
        energy -= ((speed/CELL_SPEED)*(CELL_SPEED_ENERGY_COST))+((radius/CELL_SIZE)*(CELL_SIZE_ENERGY_COST));
        Timer = 0;
    }
    if(energy >= CHILDBIRTH_ENERGY)
    {
        energy -= BIRTH_ENERGY;
        int childSpeed = this->speed;
        int childRadius = this->radius;
        Color childColor = this->color;
        int childX = position.x + (rand() % 20) - 10;
        int childY = position.y + (rand() % 20) - 10;
        if(rand() % 100 < CELL_SPEED_MUTATION_CHANCE)
        {
            childSpeed += ((rand() % 10) - 5);
        }
        if(rand() % 100 < CELL_SIZE_MUTATION_CHANCE)
        {
            childRadius += ((rand() % 10) - 5);
        }
        if(rand() % 100 < CELL_COLOR_MUTATION_CHANCE)
        {
            childColor.r += ((rand() % 100) - 50);
            childColor.g += ((rand() % 100) - 50);
            childColor.b += ((rand() % 100) - 50);
        }
        if(childSpeed < 5)
            childSpeed = 5;
        if(childRadius < 1)
            childRadius = 1;
        if(childColor.r < 0)
            childColor.r = 0;
        if(childColor.g < 0)
            childColor.g = 0;
        if(childColor.b < 0)
            childColor.b = 0;
        if(childColor.r > 255)
            childColor.r = 255;
        if(childColor.g > 255)
            childColor.g = 255;
        if(childColor.b > 255)
            childColor.b = 255;
        cells.push_back(Cell(Vec2f(childX, childY), childColor, childSpeed, BIRTH_ENERGY, childRadius, brainMove));
    }
}