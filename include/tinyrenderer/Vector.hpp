#pragma once

#include <array>       // std::array
#include <cassert>     // assert
#include <cmath>       // std::sqrt
#include <cstddef>     // size_t
#include <type_traits> // std::enable_if_t, std::is_same_v

template <typename T, size_t N>
class Vec {
  public:
    std::array<T, N> data;

    Vec() { data.fill(T(0)); }

    template <typename... Args,
              typename = std::enable_if_t<(std::is_same_v<T, Args> && ...)>>
    Vec(Args... args) : data{{args...}} {
        static_assert(sizeof...(args) == N,
                      "Number of arguments must match the dimension of the vector");
    }

    template <typename U>
    Vec(const Vec<U, N> &v) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = static_cast<T>(v[i]);
        }
    }

    void clear() { data.fill(T(0)); }

    T &operator[](int i) { return data[static_cast<size_t>(i)]; }
    const T &operator[](int i) const { return data[static_cast<size_t>(i)]; }

    Vec operator+(const Vec &v) const {
        Vec result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + v[i];
        }
        return result;
    }

    Vec operator-(const Vec &v) const {
        Vec result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - v[i];
        }
        return result;
    }

    Vec operator*(T s) const {
        Vec result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * s;
        }
        return result;
    }

    Vec operator/(T s) const {
        Vec result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] / s;
        }
        return result;
    }

    bool operator==(const Vec &v) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] != v[i]) {
                return false;
            }
        }
        return true;
    }

    double norm() const {
        double sum = 0;
        for (size_t i = 0; i < N; ++i) {
            sum += data[i] * data[i];
        }
        return std::sqrt(sum);
    }

    Vec<double, N> normalize() const {
        double n = norm();
        Vec<double, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] / n;
        }
        return result;
    }

    double length() const { return norm(); }

    Vec &operator+=(const Vec &v) {
        for (size_t i = 0; i < N; ++i) {
            data[i] += v[i];
        }
        return *this;
    }

    Vec &operator-=(const Vec &v) {
        for (size_t i = 0; i < N; ++i) {
            data[i] -= v[i];
        }
        return *this;
    }

    Vec &operator*=(T s) {
        for (size_t i = 0; i < N; ++i) {
            data[i] *= s;
        }
        return *this;
    }

    Vec &operator/=(T s) {
        for (size_t i = 0; i < N; ++i) {
            data[i] /= s;
        }
        return *this;
    }

    // Dot product
    T operator*(const Vec &v) const {
        T result = 0;
        for (size_t i = 0; i < N; ++i) {
            result += data[i] * v[i];
        }
        return result;
    }

    // Vec3 cross product
    template <typename U = T>
    typename std::enable_if<N == 3, Vec<U, 3>>::type operator^(const Vec &v) const {
        return Vec(data[1] * v[2] - data[2] * v[1], data[2] * v[0] - data[0] * v[2],
                   data[0] * v[1] - data[1] * v[0]);
    }
};

using Vec3f = Vec<float, 3>;
using Vec2f = Vec<float, 2>;
using Vec3d = Vec<double, 3>;
using Vec2d = Vec<double, 2>;
using Vec3i = Vec<int, 3>;
using Vec2i = Vec<int, 2>;
