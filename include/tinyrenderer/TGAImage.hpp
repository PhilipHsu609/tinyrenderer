#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <vector>

static_assert(true); // This is a workaround for a bug in clangd
#pragma pack(push, 1)
struct TGAHeader {
    std::uint8_t idLength;
    std::uint8_t colorMapType;
    std::uint8_t imageType;
    std::array<std::uint8_t, 5> colorMapSpec;
    std::uint16_t xOrigin;
    std::uint16_t yOrigin;
    std::uint16_t width;
    std::uint16_t height;
    std::uint8_t pixelDepth;
    std::uint8_t imageDescriptor;
};
#pragma pack(pop)

struct TGAColor {
    std::uint8_t b{}, g{}, r{}, a{};
    std::uint8_t bytespp = 1;

    TGAColor() = default;
    TGAColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
        : b(b), g(g), r(r), a(255), bytespp(3) {}
    TGAColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
        : b(b), g(g), r(r), a(a), bytespp(4) {}
    TGAColor(std::uint32_t rgba, std::uint8_t bytespp) : bytespp(bytespp) {
        this->operator()(rgba);
    }

    void operator()(std::uint32_t rgba) {
        r = (rgba >> 24) & 0xff;
        g = (rgba >> 16) & 0xff;
        b = (rgba >> 8) & 0xff;
        a = rgba & 0xff;
    }

    std::uint32_t operator()() const {
        return static_cast<uint32_t>((a << 24) | (r << 16) | (g << 8) | b);
    }
};

class TGAImage {
  public:
    TGAImage(const char *filename);
    TGAImage(std::uint16_t width, std::uint16_t height, std::uint8_t bytespp);
    void save(const char *filename) const;

    void flipVertically();
    void flipHorizontally();

    void set(std::uint16_t x, std::uint16_t y, TGAColor color);

    enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

  private:
    void load_tga_data(const char *filename);
    void write_tga_data(const char *filename, bool rle = true) const;
    void load_rle_data(std::ifstream &file);
    void write_rle_data(std::ofstream &file) const;

    std::uint16_t width = 0;
    std::uint16_t height = 0;
    std::uint8_t bytespp = 1;
    std::vector<std::uint8_t> data;
};
