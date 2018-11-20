#pragma once

#include "rectangle.hpp"
#include "common.hpp"

class Background : public Rectangle {
private:
  float textureX = 0.0f;
public:
  Background() : Rectangle(0, 3, 0, comm::UNIT_WIDTH, comm::UNIT_HEIGHT - 3,1, 90) {
    setTextureId(texture::load(config::bgTexturePath));
  }

  void update(float dt = 0) override {
    textureX -= dt / 100.f;
    setTexCoords({{textureX, 1.0f}, {1.0f + textureX, 1.0f}, {1.0f +textureX, 0.0f}, {textureX, 0.0f}});
    draw();
  }

};
