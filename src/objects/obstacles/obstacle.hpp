#pragma once

#include "common.hpp"
#include "objects/player.hpp"
#include "objects/rectangle.hpp"
#include <math.h>

class Obstacle : public Rectangle {
protected:
  float velocityX;
  float positionX = 0.0f;
  bool onCollision = false;

  // Checks if this object coordinates are inside the horizonal limits of the
  // other object.
  bool isInsideHorizontal(float otherLeft, float otherRight) {
    const float right = left + width;
    if (otherLeft <= left and left <= otherRight) {
      return true;
    }
    if (otherLeft <= right and right <= otherRight) {
      return true;
    }
    return false;
  }

  // Checks if this object coordinates are inside the vertical limits of the
  // other object.
  bool isInsideVertical(float otherBottom, float otherTop) {
    const float top = bottom + height;
    if (otherBottom <= bottom and bottom <= otherTop) {
      return true;
    }
    if (otherBottom <= top and top <= otherTop) {
      return true;
    }
    return false;
  }

public:
  Obstacle(float left, float bottom, float depth = 5.0f)
      : Rectangle(left, bottom, 1, 1, depth) {}

  void setVelocity(float velocity) { velocityX = velocity; }

  void checkCollision(float otherLeft, float otherBottom, float otherRight,
                      float otherTop) {
    // This only determines if there has been a collision, most times it can not
    // determine the position (direction) of the collision
    onCollision = false;

    const float right = left + width;
    const float top = bottom + height;
    bool a = bottom <= otherTop;
    if (bottom <= otherTop and top >= otherBottom and left <= otherRight and
        right >= otherLeft) {
      onCollision = true;
    }
  }

  virtual void action(const Player &player) {
    if (onCollision) {
      glColor3fv(comm::color::RED);
    } else {
      glColor3fv(comm::color::ORANGE);
    }
  }

  virtual void update(float dt, const Player &player) {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    checkCollision(player.getLeft(), player.getBottom(), player.getRight(),
                   player.getTop());
    action(player);

    positionX -= velocityX * dt;
    left -= velocityX * dt;

    glPushMatrix();

    glTranslatef(positionX, 0.0f, 0.0f);

    draw();

    glPopMatrix();
  }
};
