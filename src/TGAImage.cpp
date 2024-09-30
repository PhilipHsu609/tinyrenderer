#include "tinyrenderer/TGAImage.hpp"

#include <fmt/core.h>

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

TGAImage::TGAImage(const char *filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error(fmt::format("Failed to open file: {}", filename));
    }

    TGAHeader header{};
    file.read(reinterpret_cast<char *>(&header), sizeof(TGAHeader));

    width = header.width;
    height = header.height;
    bytespp = header.pixelDepth >> 3;

    if (width <= 0 || height <= 0 ||
        (bytespp != Format::GRAYSCALE && bytespp != Format::RGB &&
         bytespp != Format::RGBA)) {
        throw std::runtime_error(fmt::format("Invalid TGA file: {}", filename));
    }

    data.resize(width * height * bytespp);

    if (header.imageType == 2 || header.imageType == 3) {
        file.read(reinterpret_cast<char *>(data.data()),
                  static_cast<std::streamsize>(width * height * bytespp));
        if (!file.good()) {
            throw std::runtime_error(
                fmt::format("An error occurred while reading the file: {}", filename));
        }
    } else if (header.imageType == 10 || header.imageType == 11) {
        load_rle_data(file);
    } else {
        throw std::runtime_error(fmt::format("Unsupported TGA file type: {}", filename));
    }

    if ((header.imageDescriptor & 0x20) == 0) {
        flipVertically();
    }
    if ((header.imageDescriptor & 0x10) != 0) {
        flipHorizontally();
    }

    fmt::print("Loaded TGA image: {} ({}x{}x{})\n", filename, width, height, bytespp * 8);
}

void TGAImage::load_rle_data(std::ifstream &file) {
    const std::size_t pixelCount = width * height;
    std::size_t currentPixel = 0;
    std::uint8_t *ptr = data.data();

    while (currentPixel < pixelCount) {
        std::uint8_t chunkHeader = 0;
        file.read(reinterpret_cast<char *>(&chunkHeader), 1);
        if (!file.good()) {
            throw std::runtime_error("An error occurred while reading the file");
        }

        if (chunkHeader < 128) {
            ++chunkHeader;
            for (std::size_t i = 0; i < chunkHeader; ++i) {
                file.read(reinterpret_cast<char *>(ptr), bytespp);
                if (!file.good()) {
                    throw std::runtime_error("An error occurred while reading the file");
                }
                ++currentPixel;
                ptr += bytespp;
            }
        } else {
            chunkHeader -= 127;
            std::array<std::uint8_t, 4> pixel{};
            file.read(reinterpret_cast<char *>(pixel.data()), bytespp);
            if (!file.good()) {
                throw std::runtime_error("An error occurred while reading the file");
            }
            for (std::size_t i = 0; i < chunkHeader; ++i) {
                std::copy_n(pixel.data(), bytespp, ptr);
                ++currentPixel;
                ptr += bytespp;
            }
        }
    }
}

void TGAImage::flipVertically() {
    if (data.empty()) {
        return;
    }

    const std::size_t half = height >> 1;
    const std::size_t stride = width * bytespp;
    std::vector<std::uint8_t> buffer(stride);

    std::uint8_t *start = data.data();

    for (std::size_t i = 0; i < half; ++i) {
        std::uint8_t *line1 = &start[i * stride];
        std::uint8_t *line2 = &start[(height - 1 - i) * stride];
        std::copy(line1, line1 + stride, buffer.data());
        std::copy(line2, line2 + stride, line1);
        std::copy(buffer.begin(), buffer.end(), line2);
    }
}

void TGAImage::flipHorizontally() {
    if (data.empty()) {
        return;
    }

    const std::size_t stride = width * bytespp;
    std::uint8_t *start = data.data();

    for (std::size_t i = 0; i < height; ++i) {
        for (std::size_t j = 0; j < width / 2; ++j) {
            std::size_t index1 = i * stride + j * bytespp;
            std::size_t index2 = i * stride + (width - 1 - j) * bytespp;
            for (std::size_t k = 0; k < bytespp; ++k) {
                std::swap(start[index1 + k], start[index2 + k]);
            }
        }
    }
}