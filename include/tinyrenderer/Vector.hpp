#pragma once

#include <cmath>
#include <type_traits>

template <typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
class Vec3 {
  public:
    T x, y, z;

    Vec3(T xx = T(0), T yy = T(0), T zz = T(0)) : x(xx), y(yy), z(zz) {}

    Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(T s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(T s) const { return Vec3(x / s, y / s, z / s); }
    Vec3 operator^(const Vec3 &v) const {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    bool operator==(const Vec3 &v) const { return x == v.x && y == v.y && z == v.z; }
    T operator[](int i) const { return i == 0 ? x : (i == 1 ? y : z); }
    T operator*(const Vec3 &v) const { return x * v.x + y * v.y + z * v.z; }

    T norm() const { return std::sqrt(x * x + y * y + z * z); }
    Vec3 normalize() const { return *this / norm(); }
    T length() const { return norm(); }

    Vec3 &operator+=(const Vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    Vec3 &operator-=(const Vec3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    Vec3 &operator*=(T s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    Vec3 &operator/=(T s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
};

template <typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
class Vec2 {
  public:
    T x, y;

    Vec2(T xx = T(0), T yy = T(0)) : x(xx), y(yy) {}

    Vec2 operator+(const Vec2 &v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2 &v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(T s) const { return Vec2(x * s, y * s); }
    Vec2 operator/(T s) const { return Vec2(x / s, y / s); }
    bool operator==(const Vec2 &v) const { return x == v.x && y == v.y; }
    T operator[](int i) const { return i == 0 ? x : y; }
    T operator*(const Vec2 &v) const { return x * v.x + y * v.y; }

    T norm() const { return std::sqrt(x * x + y * y); }
    Vec2 normalize() const { return *this / norm(); }
    T length() const { return norm(); }

    Vec2 &operator+=(const Vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vec2 &operator-=(const Vec2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vec2 &operator*=(T s) {
        x *= s;
        y *= s;
        return *this;
    }
    Vec2 &operator/=(T s) {
        x /= s;
        y /= s;
        return *this;
    }
};

using Vec3f = Vec3<float>;
using Vec2f = Vec2<float>;
using Vec3d = Vec3<double>;
using Vec2d = Vec2<double>;
