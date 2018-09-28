#pragma once

#include "rectangle.hpp"

class Player : public Rectangle {
private:
  using Rectangle::draw;
  
  float black[3] = {0.0f, 0.0f, 0.0f};

  void fixPosition(bool isSliding = false) {
    glTranslatef(9.0f, 9.0f, 0.0f);
  }
public:
  Player() : Rectangle(2.0f, 6.0f, 1.0f) {}

  void jump() {

  }

  void draw(float dt) {
    glPushMatrix();
    fixPosition();

    glColor3fv(black);
    draw();
    
    glPopMatrix();
  }
};