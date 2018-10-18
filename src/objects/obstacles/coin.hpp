#pragma once

#include "obstacle.hpp"

class Coin : public Obstacle {
  // Coin is not a obstacle, but it has the same behaviours 
public:
  Coin(float left, float bottom, float depth = 5.0f)
      : Obstacle(left, bottom, depth) {
    setTextureId(texture::load(config::coinTexturePath));
  }
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (isInsideHorizontal(player.getLeft(), player.getRight())) {
          glColor3fv(comm::color::GREEN);
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

