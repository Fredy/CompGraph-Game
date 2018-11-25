#pragma once

#include "obstacle.hpp"

class Floor : public Obstacle {
public:
  Floor(float left, float bottom, float depth = 3.0f)
      : Obstacle(left, bottom,0, depth) {
    setTextureId(texture::load(config::fgTexturePath));
  }
};
