#include "tinyrenderer/Drawer.hpp"
#include "tinyrenderer/TGAImage.hpp"
#include "tinyrenderer/Vector.hpp"

#include <cmath>

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