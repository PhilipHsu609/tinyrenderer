#include "tinyrenderer/Drawer.hpp"
#include "tinyrenderer/TGAImage.hpp"
#include "tinyrenderer/Vector.hpp"

#include <array>
#include <cmath>
#include <limits>
#include <utility>

namespace {
using Vec4i = Vec<int, 4>;

// Returns bounding box [min_x, max_x, min_y, max_y] for a set of points
template <size_t N>
Vec4i find_bbox(const std::array<Vec2i, N> &pts) {
    Vec4i bbox{std::numeric_limits<int>::max(), std::numeric_limits<int>::min(),
               std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};

    for (auto const &pt : pts) {
        bbox[0] = std::min(bbox[0], pt[0]);
        bbox[1] = std::max(bbox[1], pt[0]);
        bbox[2] = std::min(bbox[2], pt[1]);
        bbox[3] = std::max(bbox[3], pt[1]);
    }

    return bbox;
}

// Returns true if point p is inside triangle t0, t1, t2
bool is_inside(Vec2f p, Vec2i t0, Vec2i t1, Vec2i t2) {
    float a = (Vec3f(t1 - t0) ^ Vec3f(p - t0))[2];
    float b = (Vec3f(t2 - t1) ^ Vec3f(p - t1))[2];
    float c = (Vec3f(t0 - t2) ^ Vec3f(p - t2))[2];
    return (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);
}
} // namespace

void line(Vec2i u, Vec2i v, TGAImage &image, TGAColor color) {
    int x0 = u[0];
    int y0 = u[1];
    int x1 = v[0];
    int y1 = v[1];

    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);

    int D = 2 * dy - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        if (D > 0) {
            y += y1 > y0 ? 1 : -1;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    const auto bbox = find_bbox(std::array{t0, t1, t2});
    for (int x = bbox[0]; x <= bbox[1]; x++) {
        for (int y = bbox[2]; y <= bbox[3]; y++) {
            Vec2f p(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f);
            if (is_inside(p, t0, t1, t2)) {
                image.set(x, y, color);
            }
        }
    }
}