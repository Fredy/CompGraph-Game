#pragma once

#include "obstacle.hpp"

class Goal : public Obstacle {

public:
  Goal(float left, float bottom)
      : Obstacle(left, bottom) {
    setTextureId(texture::load(config::coinTexturePath));
  }
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      cout << "WIN" << endl;
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }

  virtual void update(float dt, const Player &player){
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    checkCollision(player.getLeft(), player.getBottom(), player.getRight(),
                   player.getTop());
    action(player);

    positionX -= velocityX * dt;
    left -= velocityX * dt;

    glPushMatrix();

    glTranslatef(positionX, 0.0f, 0.0f);

    glPopMatrix();
  }
};


