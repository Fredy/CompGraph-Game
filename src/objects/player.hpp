#pragma once

#include "rectangle.hpp"

class Player : public Rectangle {
private:
  float black[3] = {0.0f, 0.0f, 0.0f};
  float positionY = 0.0f;
  float velocityY = 0.0f;
  float gravity = 1.0f;
  bool onGround = true;
  bool isSliding = false;
  float degree = 0.0f;

  void fixPosition() { glTranslatef(4.5f, 4.5f, 0.0f); }

  void doSlide(float dt) {
    if (isSliding) {
      if (degree < 90.0f) {
        degree += 10.0f;
      }
      glRotatef(degree, 0, 0, 1);
      glTranslatef(-1.0f, 0.0f, 0.0f);
    } else {
      if (degree > 0.0f) {
        degree -= 10.0f;
        glRotatef(degree, 0, 0, 1);
      }
    }
  }

  void doJump(float dt) {
    velocityY -= gravity;
    positionY += velocityY * dt;

    if (positionY < 0.0f) { // TODO: if the player is on a platform this must be
                            // the heigth of the platform
      positionY = 0.0f;
      velocityY = 0.0;
      onGround = true;
    }
    glTranslatef(0.0f, positionY, 0.0f);
  }

public:
  Player() : Rectangle(1.0f, 3.0f, 1.0f) {}

  void startJump() {
    if (onGround and !isSliding) {
      velocityY = 18.0f;
      onGround = false;
    }
  }
  void endJump() {
    if (velocityY > 10.0f) {
      velocityY = 10.0f;
    }
  }

  void earlyEndJump() { velocityY = 0.0f; }

  void startSlide() { isSliding = true; }
  void endSlide() { isSliding = false; }

  void draw(float dt) override {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    glPushMatrix();

    doJump(dt);
    fixPosition();
    doSlide(dt);

    glColor3fv(black);
    basicDraw();

    glPopMatrix();
  }
};
