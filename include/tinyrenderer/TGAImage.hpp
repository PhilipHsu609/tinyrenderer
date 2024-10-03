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

class TGAImage {
  public:
    TGAImage(const char *filename);
    TGAImage(std::uint16_t width, std::uint16_t height, std::uint8_t bpp);
    void save(const char *filename) const;

    void flipVertically();
    void flipHorizontally();

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
