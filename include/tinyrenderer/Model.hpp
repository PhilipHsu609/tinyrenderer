#pragma once

#include "tinyrenderer/Vector.hpp"

#include <vector>

class Model {
  public:
    Model(const char *filename);
    std::size_t nverts() const { return verts_.size(); };
    std::size_t nfaces() const { return faces_.size(); };
    Vec3f vert(std::size_t i) const { return verts_[i]; };
    std::vector<std::size_t> face(std::size_t idx) const { return faces_[idx]; };

  private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<std::size_t>> faces_;
};