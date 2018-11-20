#pragma once

#include "obstacles/obstacle.hpp"
#include "common.hpp"

class Foreground : public Rectangle {
  private:
  void update(float dt) override {}
  float textureX = 0.0f;
public:
  Foreground() : Rectangle(0, 0, 0, comm::UNIT_WIDTH, 3, 1, 2) {
    setTextureId(texture::load(config::fgTexturePath));
  }

 bool checkCollision(float otherLeft, float otherBottom, float otherRight,
                      float otherTop) {
    // This only determines if there has been a collision, most times it can not
    // determine the position (direction) of the collision

    const float right = left + width;
    const float top = bottom + height;
    if (bottom <= otherTop and top >= otherBottom and left <= otherRight and
        right >= otherLeft) {
      return true;
    }

    return false;
  }

  virtual void update(float dt, const Player &player){
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    textureX += 5.0f * dt / comm::UNIT_WIDTH;
    setTexCoords({{textureX, 1.0f}, {1.0f + textureX, 1.0f}, {1.0f +textureX, 0.0f}, {textureX, 0.0f}});
    bool collision = checkCollision(player.getLeft(), player.getBottom(), player.getRight(),
                   player.getTop());
    if (collision) {
      player.setGround(0.0f);
    }
    draw();
  }
};
