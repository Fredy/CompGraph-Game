#pragma once

#include "rectangle.hpp"

class Obstacle : public Rectangle {
  // TODO: check if every obstacle is an rectangle, this is important for
  // collisions.
private:
  const float orange[3] = {1.0f, 0.67f, 0.0f};
  float velocityX;
  float positionX = 0.0f;

public:
  Obstacle(float left, float bottom, float depth = 5.0f)
      : Rectangle(left, bottom, 1, 1, depth) {}

  void setVelocity(float velocity) { velocityX = velocity; }

  void draw(float dt) override {
    positionX -= velocityX * dt;

    glPushMatrix();
    // fixPosition();
    glTranslatef(positionX, 0.0f, 0.0f);

    glColor3fv(orange);
    basicDraw(2);

    glPopMatrix();
  }
};