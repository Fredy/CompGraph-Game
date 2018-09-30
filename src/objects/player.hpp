#pragma once

#include "rectangle.hpp"

class Player : public Rectangle {
private:
  using Rectangle::draw;

  float black[3] = {0.0f, 0.0f, 0.0f};
  float positionY = 0.0f;
  float velocityY = 0.0f;
  float gravity = 1.0f;
  bool onGround = true;

  void fixPosition(bool isSliding = false) { glTranslatef(9.0f, 9.0f, 0.0f); }

public:
  Player() : Rectangle(2.0f, 6.0f, 1.0f) {}

  void startJump() {
    if (onGround) {
      velocityY = 24.0f;
      onGround = false;
    }
  }
  void endJump() {
    if (velocityY > 12.0f) {
      velocityY = 12.0f;
    }
  }

  void draw(float dt) override {
    velocityY -= gravity;
    positionY += velocityY * dt;

    if (positionY < 0.0f) { // TODO: if the player is on a platform this must be
                            // the heigth of the platform
      positionY = 0.0f;
      velocityY = 0.0;
      onGround = true;
    }

    glPushMatrix();
    fixPosition();
    glTranslatef(0.0f, positionY, 0.0f);

    glColor3fv(black);
    draw();

    glPopMatrix();
  }
};