#pragma once

#include "rectangle.hpp"
#include "common.hpp"

class Background : public Rectangle {
private:
  float textureX = 0.0f;
public:
  Background() : Rectangle(-12,2,-10, comm::UNIT_WIDTH * 2, comm::UNIT_HEIGHT, 1) {
    setTextureId(texture::load(config::bgTexturePath));
  }

  void update(float dt = 0) override {
    textureX -= dt / 100.f;
    setTexCoords({});

    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} , // front
                  {0, 0}, {1, 0}, {1, 1}, {0, 1} , // bottom
                  {1, 1}, {0, 1}, {0, 0}, {1, 0} , // left
                  {textureX, 1.0f}, {1.0f + textureX, 1.0f}, // back 
                  {1.0f +textureX, 0.0f}, {textureX, 0.0f},  
                  {0, 1}, {1, 1}, {1, 0}, {0, 0} , // top
                  {0, 1}, {1, 1}, {1, 0}, {0, 0} }); // right
    draw();
  }

};
