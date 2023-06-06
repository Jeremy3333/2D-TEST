#pragma once
#include <cmath>

class Vec2f
{
public:
    float x;
    float y;

    Vec2f();
    Vec2f(float x, float y);
    float length() const;
    ~Vec2f();

    Vec2f &operator=(const Vec2f &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    Vec2f &operator+=(const Vec2f &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2f &operator-=(const Vec2f &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2f &operator*=(float other)
    {
        x *= other;
        y *= other;
        return *this;
    }
    Vec2f &operator/=(float other)
    {
        x /= other;
        y /= other;
        return *this;
    }
};

Vec2f operator+(const Vec2f &a, const Vec2f &b);
Vec2f operator-(const Vec2f &a, const Vec2f &b);
Vec2f operator*(const Vec2f &a, float b);
Vec2f operator/(const Vec2f &a, float b);
bool operator==(const Vec2f &a, const Vec2f &b);
bool operator!=(const Vec2f &a, const Vec2f &b);

float dot(const Vec2f &a, const Vec2f &b);
float distance(const Vec2f &a, const Vec2f &b);
Vec2f normalize(const Vec2f &a);
void driveAway(Vec2f &a, Vec2f &b, float distance, float rate);