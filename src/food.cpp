#include "Food.hpp"
#include "Utils.hpp"
#include <random>

Food::Food(Vec2f p_pos) : position(p_pos) {}

Vec2f Food::getPos() const
{
    return position;
}

Food::~Food() {}