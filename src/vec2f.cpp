#include "Vec2f.hpp"

Vec2f::Vec2f(): x(0), y(0) {}

Vec2f::Vec2f(float x, float y): x(x), y(y) {}

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

Vec2f operator+=(const Vec2f& a, const Vec2f& b)
{
    return Vec2f(a.x + b.x, a.y + b.y);
}

Vec2f operator-=(const Vec2f& a, const Vec2f& b)
{
    return Vec2f(a.x - b.x, a.y - b.y);
}

Vec2f operator*=(const Vec2f& a, float b)
{
    return Vec2f(a.x * b, a.y * b);
}

Vec2f operator/=(const Vec2f& a, float b)
{
    return Vec2f(a.x / b, a.y / b);
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

void driveAway(Vec2f& a, const Vec2f& b, float distance)
{
    // drave a and b away from each other half the distance each
    Vec2f direction = normalize(a - b);
    a += direction * distance / 2;
    b -= direction * distance / 2;
}