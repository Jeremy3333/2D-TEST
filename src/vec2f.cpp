#include "Vec2f.hpp"

Vec2f::Vec2f(): x(0), y(0) {}

Vec2f::Vec2f(float x, float y): x(x), y(y) {}

float Vec2f::length() const
{
    return sqrt(x * x + y * y);
}

Vec2f::~Vec2f() {}


Vec2f operator+(const Vec2f& a, const Vec2f& b)
{
    return Vec2f(a.x + b.x, a.y + b.y);
}

Vec2f operator-(const Vec2f& a, const Vec2f& b)
{
    return Vec2f(a.x - b.x, a.y - b.y);
}

Vec2f operator*(const Vec2f& a, float b)
{
    return Vec2f(a.x * b, a.y * b);
}

Vec2f operator/(const Vec2f& a, float b)
{
    return Vec2f(a.x / b, a.y / b);
}

bool operator==(const Vec2f& a, const Vec2f& b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vec2f& a, const Vec2f& b)
{
    return !(a == b);
}

float dot(const Vec2f& a, const Vec2f& b)
{
    return a.x * b.x + a.y * b.y;
}

float distance(const Vec2f& a, const Vec2f& b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Vec2f normalize(const Vec2f& a)
{
    return a / sqrt(pow(a.x, 2) + pow(a.y, 2));
}

void driveAway(Vec2f& vec1,  Vec2f& vec2, float distance, float rate)
{
    Vec2f dist = vec1 - vec2;
    Vec2f norm = normalize(dist);
    Vec2f force = norm * distance;
    vec1 = vec1 + force * (1 - rate);
    vec2 = vec2 - force * rate;
}