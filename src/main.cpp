#include "tinyrenderer/Drawer.hpp"
#include "tinyrenderer/Model.hpp"
#include "tinyrenderer/TGAImage.hpp"

#include <fmt/core.h>

#include <cassert>

int main() {
    constexpr int width = 200;
    constexpr int height = 200;

    TGAImage image(width, height, TGAImage::RGB);

    Vec2i t0[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
    Vec2i t1[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

    triangle(t0[0], t0[1], t0[2], image, RED_COLOR);
    triangle(t1[0], t1[1], t1[2], image, WHITE_COLOR);
    triangle(t2[0], t2[1], t2[2], image, GREEN_COLOR);

    image.flipVertically();
    image.save("output.tga");

    return 0;
}