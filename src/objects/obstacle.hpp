#pragma once

#include "rectangle.hpp"

class Obstacle : public Rectangle {
  // TODO: check if every obstacle is an rectangle, this is important for
  // collisions.
private:
  using Rectangle::draw;

  const float orange[3] = {1.0f, 0.67f, 0.0f};
  float velocityX;
  float positionX = 0.0f;

public:
  Obstacle(float left, float bottom, float width, float height,
           float depth = 5.0f)
      : Rectangle(left, bottom, width, height, depth) {}

  void setVelocity(float velocity) {
    velocityX = velocity;
  }

  void draw(float dt) {
    positionX -= velocityX * dt;

    glPushMatrix();
    //fixPosition();
    glTranslatef(positionX, 0.0f, 0.0f);

    glColor3fv(orange);
    draw();

    glPopMatrix();
  }

};