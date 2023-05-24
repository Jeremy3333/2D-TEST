#pragma once
#include <vector>

#include "Cell.hpp"

class World
{

public:
    std::vector<Cell> cells;
    World();
    ~World();
    void Update(float dt);
};