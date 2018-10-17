#pragma once

#include "obstacle.hpp"

class Block : public Obstacle {
  using Obstacle::Obstacle;
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (isInsideHorizontal(player.getLeft(), player.getRight())) {
        if (top - 0.1f <= player.getBottom() + 0.25f) {
          player.setGround(bottom + height - 3);
          glColor3fv(comm::color::GREEN);
        } else {
          // Player is bellow the obstacle
          glColor3fv(comm::color::RED);
        }
      } else if (isInsideVertical(player.getBottom(), player.getTop())) {
        if (left <= player.getRight()) {
          // Player is in the right side of the obstacle
        }
      }
    } else {
      glColor3fv(comm::color::ORANGE);
    }
  }
};
