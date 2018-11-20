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
      if (isInsideHorizontal(player.getLeft(), player.getRight())) {
        // -0.1 and +0.25 are the limit window, without that the collision is
        // not detected.
        if (top - 0.1f <= player.getBottom() + 0.25f) {
          // TODO: move this '3', it's the foreground height
          player.setGround(bottom + height - 3);
          glColor3fv(comm::color::GREEN);
        } else {
          // Player is bellow the obstacle
          glColor3fv(comm::color::RED);
        }
      } else if (isInsideVertical(player.getBottom(), player.getTop())) {
        if (left <= player.getRight()) {
          // Player is in the right side of the obstacle
          cout << "loose" << endl;
        }
      }
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }
};
