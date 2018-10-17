#pragma once

#include "rectangle.hpp"

const float PLAYER_FIX_POS = 4.5f;

class Player : public Rectangle {
private:
  float black[3] = {0.0f, 0.0f, 0.0f};
  float positionY = 0.0f;
  float velocityY = 0.0f;
  float gravity = 1.0f;
  bool onGround = true;
  bool isSliding = false;
  float degree = 0.0f;
  float ground = 0.0f;

  void fixPosition() { glTranslatef(PLAYER_FIX_POS, PLAYER_FIX_POS, 0.0f); }

  void doSlide(float dt) {
    if (isSliding) {
      if (degree < 90.0f) {
        degree += 10.0f;
      }
      glRotatef(degree, 0, 0, 1);
      left = PLAYER_FIX_POS + 0.5f;
      bottom = ground + 1.0f;
      glTranslatef(-1.0f, 0.0f, 0.0f);
    } else {
      if (degree > 0.0f) {
        degree -= 10.0f;
        glRotatef(degree, 0, 0, 1);
        left = PLAYER_FIX_POS - 0.5f;
        bottom = -height / 2.0f + PLAYER_FIX_POS;
      }
    }
  }

  void doJump(float dt) {
    velocityY -= gravity;
    positionY += velocityY * dt;
    bottom = positionY + PLAYER_FIX_POS - height / 2.0;
    if (positionY < ground) {
      positionY = ground;
      bottom = positionY + PLAYER_FIX_POS - height / 2.0;
      velocityY = 0.0;
      onGround = true;
    }
    glTranslatef(0.0f, positionY, 0.0f);
  }

public:
  Player() : Rectangle(1.0f, 3.0f, 1.0f) {
    bottom = PLAYER_FIX_POS - height / 2.0;
    left = PLAYER_FIX_POS - width / 2.0f;
  }

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

    cout << "B: " << bottom << " L: " << left << endl;
    glPushMatrix();

    doJump(dt);
    fixPosition();
    doSlide(dt);

    glColor3fv(black);
    basicDraw();

    glPopMatrix();
  }

  float getBottom() const { return bottom; }

  float getLeft() const  { return left; }

  float getRight() const { return left + width; }

  float getUp() const { return bottom + height; }

  void setGround(float ground) { this->ground = ground; }
};
