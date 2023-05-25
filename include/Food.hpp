#pragma once
#include "Vec2f.hpp"

class Food
{
private:
    Vec2f position;

public:
    Food(Vec2f p_pos);

    Vec2f getPos() const;

    ~Food();

};