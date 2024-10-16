#include "tinyrenderer/Drawer.hpp"
#include "tinyrenderer/TGAImage.hpp"

#include <cmath>

int main() {
    TGAImage img(100, 100, TGAImage::RGB);

    TGAColor red(255, 0, 0, 255);
    TGAColor white(255, 255, 255, 255);

    for (int degree = 0; degree <= 180; degree += 5) {
        const double radian = degree * M_PI / 180.0;
        const int x0 = static_cast<int>(50 + 40 * std::cos(radian));
        const int y0 = static_cast<int>(50 + 40 * std::sin(radian));
        // opposite points of a circle
        const int x1 = static_cast<int>(50 + 40 * std::cos(radian + M_PI));
        const int y1 = static_cast<int>(50 + 40 * std::sin(radian + M_PI));
        line(x0, y0, x1, y1, img, red);
    }

    img.flipVertically();
    img.save("output.tga");

    return 0;
}