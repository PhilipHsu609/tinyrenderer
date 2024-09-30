#include "tinyrenderer/TGAImage.hpp"

#include <fmt/core.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fmt::print("Usage: {} <filename>\n", argv[0]);
        return 1;
    }

    TGAImage image(argv[1]);
    return 0;
}