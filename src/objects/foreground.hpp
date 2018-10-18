#pragma once

#include "rectangle.hpp"
#include "common.hpp"

class Foreground : public Rectangle {
public:
  Foreground() : Rectangle(0, 0, comm::UNIT_WIDTH, 3, 2) {
    setTextureId(texture::load(config::fgTexturePath));
  }

  void update(float dt = 0) override {
    draw();
  }

};