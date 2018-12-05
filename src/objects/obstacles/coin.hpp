#pragma once

#include "obstacle.hpp"

class Coin : public Obstacle {
private:
  bool isTransparent = false;
  // Coin is not a obstacle, but it has the same behaviours 
public:
  Coin(float left, float bottom)
      : Obstacle(left, bottom) {
    setTextureId(texture::load(config::coinTexturePath));
  }
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (isInsideHorizontal(player.getLeft(), player.getRight())) {
        // setTextureId(texture::load(config::invisibleTexturePath));
        isTransparent = true;
      } else if (isInsideVertical(player.getBottom(), player.getTop())) {
        if (left <= player.getRight()) {
          // Player is in the right side of the obstacle
        }
      }
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

    if (!isTransparent) {
      draw();
    }

    glPopMatrix();
  }
};

