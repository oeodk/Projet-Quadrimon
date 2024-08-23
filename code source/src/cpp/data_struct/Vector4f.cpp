#include "data_struct/Vector4f.h"

namespace bdm

{
    Vector4f::Vector4f(float px, float py, float pz, float pt)
        : x(px), y(py), z(pz), t(pt)
    {

    }

    Vector4f::Vector4f(Vector3f v, float pt)
        : x(v.x), y(v.y), z(v.z), t(pt)
    {

    }

    void Vector4f::normalize()
    {
        float norm = std::sqrt(x * x + y * y + z * z + t * t);
        x /= norm;
        y /= norm;
        z /= norm;
        t /= norm;
    }


    void Vector4f::set(float vx, float vy, float vz, float vt)
    {
        x = vx;
        y = vy;
        z = vz;
        t = vt;
    }

    void Vector4f::operator*=(float value)
    {
        x *= value;
        y *= value;
        z *= value;
        t *= value;
    }

    void Vector4f::operator/=(float value)
    {
        x /= value;
        y /= value;
        z /= value;
        t /= value;
    }

    void Vector4f::operator+=(float value)
    {
        x += value;
        y += value;
        z += value;
        t += value;
    }

    void Vector4f::operator-=(float value)
    {
        x -= value;
        y -= value;
        z -= value;
        t -= value;
    }

    void Vector4f::operator+=(const Vector4f& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        t += v.t;
    }

    void Vector4f::operator-=(const Vector4f& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        t -= v.t;
    }

    Vector4f operator+(const Vector4f& v1, const Vector4f& v2)
    {
        return Vector4f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.t + v2.t);
    }

    Vector4f operator-(const Vector4f& v1, const Vector4f& v2)
    {
        return Vector4f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.t - v2.t);
    }
    Vector4f operator*(const Vector4f& v1, float value)
    {
        return Vector4f(v1.x * value, v1.y * value, v1.z * value, v1.t * value);
    }
    Vector4f operator/(const Vector4f& v1, float value)
    {
        return Vector4f(v1.x / value, v1.y / value, v1.z / value, v1.t / value);
    }
}
