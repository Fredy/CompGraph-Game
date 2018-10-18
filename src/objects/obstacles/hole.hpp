#pragma once

#include "obstacle.hpp"

class Hole : public Obstacle {
private:
  float groupLeft;
  float groupWidth;

  // Checks if the other object is completely inside the hole
  bool isCompletelyInsideHorizontal(float otherLeft, float otherRight) {
    const float groupRight = groupLeft + groupWidth;
    return (groupLeft <= otherLeft and otherLeft <= groupRight and
            groupLeft <= otherRight and otherRight <= groupRight);
  }

public:
  Hole(float left, float bottom, float depth = 1.0f)
      : Obstacle(left, bottom, depth) {
    setTextureId(texture::load(config::holeTexturePath));
  }

  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (isCompletelyInsideHorizontal(player.getLeft(), player.getRight())) {
        glColor3fv(comm::color::RED);
        // TODO: set ground to -3.0f and end the game
      }
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }

  void setGroupLeft(float left) { groupLeft = left; }

  void setGroupWidth(float width) { groupWidth = width; }

  void update(float dt, const Player &player) override {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    checkCollision(player.getLeft(), player.getBottom(), player.getRight(),
                   player.getTop());
    action(player);

    const float realVel = velocityX * dt;
    positionX -= realVel;
    left -= realVel;
    groupLeft -= realVel;

    glPushMatrix();

    glTranslatef(positionX, 0.0f, 0.0f);

    draw();

    glPopMatrix();
  }
};
