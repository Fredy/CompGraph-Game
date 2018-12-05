#pragma once

#include "common.hpp"
#include "objects/player.hpp"
#include "objects/rectangle.hpp"
#include <math.h>

class Obstacle : public Rectangle {
private:
  void update(float dt) override {}

protected:
  float velocityX;
  float positionX = 0.0f;
  bool onCollision = false;
  bool topCollision = false;
  bool bottomLeftCollision = false;

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

  bool checkTopCollision(float otherLeft, float otherBottom, float otherRight,
                         float otherTop, float topWindow = 0.4f) {
    const float right = left + width;
    const float top = bottom + height;
    const float windowBottom = top - topWindow;
    return (windowBottom <= otherTop and top >= otherBottom and
            left <= otherRight and right >= otherLeft);
  }

  bool checkBotLeftCollision(float otherLeft, float otherBottom,
                             float otherRight, float otherTop,
                             float topWindow = 0.4f) {
    const float right = left + width;
    const float top = bottom + height - topWindow;
    return (bottom <= otherTop and top >= otherBottom and left <= otherRight and
            right >= otherLeft);
  }

public:
    Obstacle(float left, float bottom, float z = 1, float sizeZ = 1.0f)
      : Rectangle(left, bottom, z, 1, 1, sizeZ) {}

  void setVelocity(float velocity) { velocityX = velocity; }

  void checkCollision(float otherLeft, float otherBottom, float otherRight,
                      float otherTop) {
    // This only determines if there has been a collision, most times it can not
    // determine the position (direction) of the collision
    onCollision = false;
    bottomLeftCollision = false;
    topCollision = false;

    if (checkBotLeftCollision(otherLeft, otherBottom, otherRight, otherTop)) {
      bottomLeftCollision = true;
      onCollision = true;
      return;
    }
    if (checkTopCollision(otherLeft, otherBottom, otherRight, otherTop)) {
      topCollision = true;
      onCollision = true;
      return;
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
