#pragma once

#include "tinyrenderer/TGAImage.hpp"
#include "tinyrenderer/Vector.hpp"

void line(Vec2i u, Vec2i v, TGAImage &image, TGAColor color);

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);