#pragma once

#include "rectangle.hpp"
#include "common.hpp"

class Background : public Rectangle {
public:
  Background() : Rectangle(0, 0, comm::UNIT_WIDTH, comm::UNIT_HEIGHT, 90) {
    //setTextureId(texture::load());
  }

  void update(float dt = 0) override {
    draw();
  }

};