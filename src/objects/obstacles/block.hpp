#pragma once

#include "obstacle.hpp"

class Block : public Obstacle {
public:
  Block(float left, float bottom, float depth = 5.0f)
      : Obstacle(left, bottom, depth) {
    setTextureId(texture::load(config::blockTexturePath));
  }
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (bottomLeftCollision) {
        glColor3fv(comm::color::RED);
      }
      if (topCollision) {
        player.setGround(bottom + height - 3);
        glColor3fv(comm::color::GREEN);
      }
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }
};
