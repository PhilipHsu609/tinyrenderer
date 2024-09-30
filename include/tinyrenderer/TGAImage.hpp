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

  private:
    void flipVertically();
    void flipHorizontally();
    void load_rle_data(std::ifstream &file);

  private:
    enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

    std::size_t width;
    std::size_t height;
    std::uint8_t bytespp;
    std::vector<std::uint8_t> data;
};
