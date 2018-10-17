#pragma once

#include "common.hpp"
#include "rectangle.hpp"
#include <math.h>

struct Colliders {
  bool left;
  bool right;
  bool top;
  bool bottom;

  void allFalse() { left = right = top = bottom = false; }
};

class Obstacle : public Rectangle {
  // TODO: check if every obstacle is an rectangle, this is important for
  // collisions.
private:
  using Rectangle::draw;

  const float orange[3] = {1.0f, 0.67f, 0.0f};
  const float red[3] = {1.0f, 0.0f, 0.0f};
  float velocityX;
  float positionX = 0.0f;
  Colliders colliders;
  bool onCollision = false;

public:
  Obstacle(float left, float bottom, float depth = 5.0f)
      : Rectangle(left, bottom, 1, 1, depth) {
  }

  void setVelocity(float velocity) { velocityX = velocity; }

  void checkCollision(float otherLeft, float otherBottom, float otherRight,
                         float otherTop) {
    colliders.allFalse();
    onCollision = false;
    if (left <= otherRight) {
      // rightCollision
      colliders.left = true;
    }
    if (bottom < otherTop) {
      // topCollision
      colliders.bottom = true;
    }
    if (bottom + height >= otherBottom) {
      // downCollision
      colliders.top = true;
    }
    if (left + width > otherLeft) {
      // leftCollision
      colliders.right = true;
    }
    if (colliders.left && colliders.top && colliders.right &&
        colliders.bottom) {
      onCollision = true;
    }
  }

  void action() {
    if (onCollision) {
      glColor3fv(red);
    } else {
      glColor3fv(orange);
    }
  }

  void draw(float dt) override {
    positionX -= velocityX * dt;
    left -= velocityX * dt;

    glPushMatrix();
    glTranslatef(positionX, 0.0f, 0.0f);

    action();
    draw();

    glPopMatrix();
  }
};
