#pragma once

#include "common.hpp"
#include "obstacles/obstacle.hpp"

class Foreground : public Rectangle {
private:
  void update(float dt) override {}
  float textureX = 0.0f;

public:
  Foreground() : Rectangle(0, 0, comm::UNIT_WIDTH, 3, 2) {
    setTextureId(texture::load(config::fgTexturePath));
  }

  bool checkCollision(float otherBottom, float otherTop) {
    // This only determines if there has been a collision, most times it can not
    // determine the position (direction) of the collision

    const float top = bottom + height;
    return (bottom <= otherTop and top >= otherBottom);
  }

  virtual void update(float dt, const Player &player) {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    textureX += 5.0f * dt / comm::UNIT_WIDTH;
    setTexCoords({{textureX, 1.0f},
                  {1.0f + textureX, 1.0f},
                  {1.0f + textureX, 0.0f},
                  {textureX, 0.0f}});
    bool collision = checkCollision(player.getBottom(), player.getTop());
    if (collision) {
      player.setGround(0.0f);
    }
    draw();
  }
};