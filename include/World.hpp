#pragma once
#include <vector>

#include "Cell.hpp"
#include "Food.hpp"

class World
{

public:
    std::vector<Cell> cells;
    std::vector<Food> foods;
    World();
    ~World();
    void Update(float dt);
};