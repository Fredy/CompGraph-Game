#pragma once

#include "obstacle.hpp"

class Rock : public Obstacle {
public:
  Rock(float left, float bottom, float depth = 5.0f)
      : Obstacle(left, bottom, depth) {
    setTextureId(texture::load(config::rockTexturePath));
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
          cout << "loose" << endl;
        }
      }
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }
};
