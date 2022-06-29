#pragma once
#include <cmath>

namespace SS::Math
{
    // Vector
    class Vector
    {
    public:
        float x, y, z;

        Vector operator+(const Vector &v) const
        {
            return Vector{x + v.x, y + v.y, z + v.z};
        }

        Vector operator-(const Vector &v) const
        {
            return Vector{x - v.x, y - v.y, z - v.z};
        }

        Vector operator*(const Vector &v) const
        {
            return Vector{x * v.x, y * v.y, z * v.z};
        }

        Vector operator/(const Vector &v) const
        {
            return Vector{x / v.x, y / v.y, z / v.z};
        }

        float Size()
        {
            return std::sqrt((x * x) + (y * y) + (z * z));
        }
    };

    // Vector2
    class Vector2
    {
    public:
        float x, y;

        Vector2 operator+(const Vector2 &v) const
        {
            return Vector2{x + v.x, y + v.y};
        }

        Vector2 operator-(const Vector2 &v) const
        {
            return Vector2{x - v.x, y - v.y};
        }

        Vector2 operator*(const Vector2 &v) const
        {
            return Vector2{x * v.x, y * v.y};
        }

        Vector2 operator/(const Vector2 &v) const
        {
            return Vector2{x / v.x, y / v.y};
        }

        float Size()
        {
            return std::sqrt((x * x) + (y * y));
        }
    };
} // namespace SS::Math
