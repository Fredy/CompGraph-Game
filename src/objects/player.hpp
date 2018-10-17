#pragma once

#include "rectangle.hpp"

const float fixPos = 4.5f;

class Player : public Rectangle {
private:
  using Rectangle::draw;

  float black[3] = {0.0f, 0.0f, 0.0f};
  float positionY = 0.0f;
  float velocityY = 0.0f;
  float gravity = 1.0f;
  bool onGround = true;
  bool isSliding = false;
  float degree = 0.0f;
  float width;
  float height;
  float bottom;
  float left;
  float ground = 0.0f;  
  void fixPosition() { glTranslatef(fixPos, fixPos, 0.0f); }

  void doSlide(float dt) {
    if (isSliding) {
      if (degree < 90.0f) {
        degree += 10.0f;
      }
      glRotatef(degree, 0, 0, 1);
      left = fixPos+0.5f;
      bottom = ground + 1.0f;      
      glTranslatef(-1.0f, 0.0f, 0.0f);
    } else {
      if (degree > 0.0f) {
        degree -= 10.0f;
        glRotatef(degree, 0, 0, 1);
        left = fixPos-0.5f;
        bottom = -height/ 2.0f + fixPos;
      }
    }
  }

  void doJump(float dt) {
    velocityY -= gravity;
    positionY += velocityY * dt;
    bottom += positionY;
    if (positionY < ground) { // TODO: if the player is on a platform this must be
                            // the heigth of the platform
      positionY = ground;
      bottom = -height/ 2.0f + fixPos;
      velocityY = 0.0;
      onGround = true;
    }
    
    glTranslatef(0.0f, positionY, 0.0f);
  }

public:
  Player() : Rectangle(1.0f, 3.0f, 1.0f) {
    width = 1.0f;
    height = 3.0f;    
    bottom = -height/ 2.0f + fixPos;
    left = -width / 2.0f + fixPos;
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
    glPushMatrix();

    doJump(dt);
    fixPosition();
    doSlide(dt);

    glColor3fv(black);
    draw();

    glPopMatrix();
  }

  float getBottom(){ return bottom;}

  float getLeft(){ return left;} 
  
  float getRight(){ return left + width;}

  float getUp(){ return bottom + height;}
};
