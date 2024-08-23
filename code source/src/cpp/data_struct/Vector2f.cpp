#include "data_struct/Vector2f.h"

namespace bdm

{
    Vector2f::Vector2f(float px, float py)
        : x(px), y(py)
    {

    }

    void Vector2f::normalize()
    {
        float norm = std::sqrt(x * x + y * y);
        x /= norm;
        y /= norm;
    }


    void Vector2f::set(float vx, float vy)
    {
        x = vx;
        y = vy;
    }

    void Vector2f::operator*=(float value)
    {
        x *= value;
        y *= value;
    }

    void Vector2f::operator/=(float value)
    {
        x /= value;
        y /= value;
    }

    void Vector2f::operator+=(float value)
    {
        x += value;
        y += value;
    }

    void Vector2f::operator-=(float value)
    {
        x -= value;
        y -= value;
    }

    void Vector2f::operator+=(const Vector2f& v)
    {
        x += v.x;
        y += v.y;
    }

    void Vector2f::operator-=(const Vector2f& v)
    {
        x -= v.x;
        y -= v.y;
    }

    Vector2f operator+(const Vector2f& v1, const Vector2f& v2)
    {
        return Vector2f(v1.x + v2.x, v1.y + v2.y);
    }

    Vector2f operator-(const Vector2f& v1, const Vector2f& v2)
    {
        return Vector2f(v1.x - v2.x, v1.y - v2.y);
    }
    Vector2f operator*(const Vector2f& v1, float value)
    {
        return Vector2f(v1.x * value, v1.y * value);
    }
    Vector2f operator/(const Vector2f& v1, float value)
    {
        return Vector2f(v1.x / value, v1.y / value);
    }
}
