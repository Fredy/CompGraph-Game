#pragma once

#include "obstacle.hpp"

class Rock : public Obstacle {
private:
  float anim = 0.0f;
  int spriteIt = 0;
  float spriteHeight = 1.0f / 32.0f; // TODO: calculate this!

  void updateTexCoords(float dt) {
    anim += dt;
    if (anim <= dt*5.0f) {
      return;
    }
    spriteIt++;
    anim = 0.0f;
    if (spriteIt == 32) {
      spriteIt = 0;
    }
    setTexCoords({{0, spriteHeight * (spriteIt + 1)},
                  {1, spriteHeight * (spriteIt + 1)},
                  {1, spriteHeight * spriteIt},
                  {0, spriteHeight * spriteIt}});
  }


public:
  Rock(float left, float bottom)
      : Obstacle(left, bottom) {
    setTextureId(texture::load(config::rockTexturePath));
    setTexCoords({{0, spriteHeight}, {1, spriteHeight}, {1,0}, {0, 0}});
  }
  void action(const Player &player) override {
    const float right = left + width;
    const float top = bottom + height;
    if (onCollision) {
      if (isInsideHorizontal(player.getLeft(), player.getRight())) {
        glColor3fv(comm::color::RED);
      } else if (isInsideVertical(player.getBottom(), player.getTop())) {
        if (left <= player.getRight()) {
          // Player is in the right side of the obstacle
        }
      }
    } else {
      glColor3fv(comm::color::WHITE);
    }
  }

  virtual void update(float dt, const Player &player) {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()

    // setTexCoords()
    checkCollision(player.getLeft(), player.getBottom(), player.getRight(),
                   player.getTop());
    action(player);

    positionX -= velocityX * dt;
    left -= velocityX * dt;

    glPushMatrix();
    //updateTexCoords(dt);
    glTranslatef(positionX, 0.0f, 0.0f);
    setTexCoords({});

    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} , // front
                  {0, 0}, {1, 0}, {1, 1}, {0, 1} , // bottom
                  {1, 1}, {0, 1}, {0, 0}, {1, 0} , // left
                  {0, 1.0f}, {1.0f, 1.0f}, // back 
                  {1.0f, 0.0f}, {0, 0.0f},  
                  {0, 0}, {0, 0}, {0, 0}, {0, 0} , // top
                  {0, 1}, {1, 1}, {1, 0}, {0, 0} }); // right
    draw();

    glPopMatrix();
  }
};
