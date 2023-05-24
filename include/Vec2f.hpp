#pragma once
#include <cmath>

class Vec2f
{
public:
    float x;
    float y;

    Vec2f();
    Vec2f(float x, float y);
    ~Vec2f();

};

Vec2f operator+(const Vec2f& a, const Vec2f& b);
Vec2f operator-(const Vec2f& a, const Vec2f& b);
Vec2f operator*(const Vec2f& a, float b);
Vec2f operator/(const Vec2f& a, float b);
bool operator==(const Vec2f& a, const Vec2f& b);
bool operator!=(const Vec2f& a, const Vec2f& b);
Vec2f operator+=(const Vec2f& a, const Vec2f& b);
Vec2f operator-=(const Vec2f& a, const Vec2f& b);
Vec2f operator*=(const Vec2f& a, float b);
Vec2f operator/=(const Vec2f& a, float b);

float dot(const Vec2f& a, const Vec2f& b);
float distance(const Vec2f& a, const Vec2f& b);
Vec2f normalize(const Vec2f& a);
void driveAway(Vec2f& a, const Vec2f& b, float distance);