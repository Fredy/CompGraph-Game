#pragma once

#include "obstacle.hpp"

class FireBall : public Obstacle {
public:
  FireBall(float left, float bottom)
      : Obstacle(left, bottom, 1.0f, 0.7f, 0.7f, 0.7f) {
    setTextureId(texture::load(config::fireBallTexturePath));
  }
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (isInsideHorizontal(player.getLeft(), player.getRight())) {
        glColor3fv(comm::color::RED);
      } else if (isInsideVertical(player.getBottom(), player.getTop())) {
        if (left <= player.getRight()) {
          // Player is in the right side of the obstacle
        }
      }
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }
};
