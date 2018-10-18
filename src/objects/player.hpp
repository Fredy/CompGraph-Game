#pragma once

#include "rectangle.hpp"
#include "common.hpp"
#include <iostream>
using namespace std;


class Player : public Rectangle {
private:
  const float PLAYER_FIX_POS = 4.5f;
  float positionY = 0.0f;
  float velocityY = 0.0f;
  float gravity = 1.0f;
  bool onGround = true;
  bool isSliding = false;
  float degree = 0.0f;
  mutable float ground = 0.0f;

  void fixPosition() { glTranslatef(PLAYER_FIX_POS, PLAYER_FIX_POS, 0.0f); }

  void doSlide(float dt) {
    if (isSliding) {
      if (degree < 90.0f) {
        degree += 10.0f;
      }
      glRotatef(degree, 0, 0, 1);
      left = PLAYER_FIX_POS + width / 2.0f;
      bottom = ground + 1.0f;
      height = 1.0f;
      width = 3.0f;
      glTranslatef(-1.0f, 0.0f, 0.0f);
    } else {
      if (degree > 0.0f) {
        degree -= 10.0f;
        glRotatef(degree, 0, 0, 1);
        left = PLAYER_FIX_POS - width / 2.0f;
        bottom = -height / 2.0f + PLAYER_FIX_POS;
        height = 3.0f;
        width = 1.0f;
      }
    }
  }

  void doJump(float dt) {
    velocityY -= gravity;
    positionY += velocityY * dt;
    if (positionY < ground) {
      positionY = ground;
      velocityY = 0.0;
      onGround = true;
    }
    bottom = positionY + PLAYER_FIX_POS - height / 2.0;
    glTranslatef(0.0f, positionY, 0.0f);
    ground = 0.0f;
  }

public:
  Player() : Rectangle(1.0f, 3.0f, 1.0f) {
    bottom = PLAYER_FIX_POS - height / 2.0;
    left = PLAYER_FIX_POS - width / 2.0f;
  }

  void startJump() {
    if (onGround and !isSliding) {
      velocityY = 18.0f + ground;
      onGround = false;
    }
  }
  void endJump() {
    if (velocityY > 10.0f + ground) {
      velocityY = 10.0f + ground;
    }
  }

  void earlyEndJump() { velocityY = 0.0f; }

  void startSlide() { isSliding = true; }
  void endSlide() { isSliding = false; }

  void update(float dt) override {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()

    //cout << "B: " << bottom << " L: " << left << endl;
    glPushMatrix();

    doJump(dt);
    fixPosition();
    doSlide(dt);

    glColor3fv(comm::color::BLACK);
    draw();

    glPopMatrix();

  }

  float getBottom() const { return bottom; }

  float getLeft() const { return left; }

  float getRight() const { return left + width; }

  float getTop() const { return bottom + height; }

  void setGround(float ground) const { this->ground = ground; }
};
