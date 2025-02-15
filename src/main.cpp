#include "tinyrenderer/Drawer.hpp"
#include "tinyrenderer/Model.hpp"
#include "tinyrenderer/TGAImage.hpp"

#include <fmt/core.h>

#include <cassert>

int main() {
    constexpr int width = 800;
    constexpr int height = 800;

    TGAImage image(width, height, TGAImage::RGB);
    TGAColor white(255, 255, 255, 255);

    Model model("obj/african_head/african_head.obj");

    fmt::print("nverts: {}\n", model.nverts());
    fmt::print("nfaces: {}\n", model.nfaces());

    for (std::size_t i = 0; i < model.nfaces(); i++) {
        std::vector<std::size_t> face = model.face(i);
        for (std::size_t j = 0; j < face.size(); j++) {
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[(j + 1) % face.size()]);
            auto x0 = static_cast<int>((v0[0] + 1.f) / 2.f * (width - 1));
            auto y0 = static_cast<int>((v0[1] + 1.f) / 2.f * (height - 1));
            auto x1 = static_cast<int>((v1[0] + 1.f) / 2.f * (width - 1));
            auto y1 = static_cast<int>((v1[1] + 1.f) / 2.f * (height - 1));
            ::line(Vec2i(x0, y0), Vec2i(x1, y1), image, white);
        }
    }

    image.flipVertically();
    image.save("output.tga");

    return 0;
}