#include "data_struct/Vector3f.h"
#include "data_struct/Vector4f.h"

namespace bdm

{
    Vector3f::Vector3f(float px, float py, float pz)
        : x(px), y(py), z(pz)
    {
        
    }

    void Vector3f::normalize()
    {
        float norm = std::sqrt(x * x + y * y + z * z);
        x /= norm;
        y /= norm;
        z /= norm;
    }

    void Vector3f::invert()
    {
        x = -x;
        y = -y;
        z = -z;
    }


    void Vector3f::set(float vx, float vy, float vz)
    {
        x = vx;
        y = vy;
        z = vz;
    }

    void Vector3f::operator*=(float value)
    {
        x *= value;
        y *= value;
        z *= value;
    }

    void Vector3f::operator/=(float value)
    {
        x  /= value;
        y  /= value;
        z  /= value;
    }

    void Vector3f::operator+=(float value)
    {
        x += value;
        y += value;
        z += value;
    }

    void Vector3f::operator-=(float value)
    {
        x -= value;
        y -= value;
        z -= value;
    }

    void Vector3f::operator+=(const Vector3f& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void Vector3f::operator-=(const Vector3f& v)
    {
        x -= v.x; 
        y -= v.y;
        z -= v.z;
    }

    Vector3f operator+(const Vector3f& v1, const Vector3f& v2)
    {
        return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    Vector3f operator-(const Vector3f& v1, const Vector3f& v2)
    {
        return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }
    Vector3f operator*(const QMatrix4x4& transformation_matrix, const Vector3f& v1)
    {
        QVector4D transformed_vec(transformation_matrix * QVector4D(v1.x, v1.y, v1.z, 1));
        return Vector3f(transformed_vec.x(), transformed_vec.y(), transformed_vec.z()) / transformed_vec.w();
    }
    Vector3f operator*(const Vector3f& v1, float value)
    {
        return Vector3f(v1.x * value, v1.y * value, v1.z * value);
    }
    Vector3f operator/(const Vector3f& v1, float value)
    {
        return Vector3f(v1.x / value, v1.y / value, v1.z / value);
    }
    Vector3f crossProduct(const Vector3f& v1, const Vector3f& v2)
    {
        return Vector3f(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
}
