#pragma once

#include "obstacles/obstacle.hpp"
class InitialFloor : public Obstacle {
private:

public:
  InitialFloor(float x, float y, float sizeZ = 3)
      : Obstacle(x, y, 0, comm::UNIT_WIDTH, 3, sizeZ) {
    setTextureId(texture::load(config::fgTexturePath));

    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} , // front
                {0, 0}, {1, 0}, {1, 1}, {0, 1} , // bottom
                {1, 1}, {0, 1}, {0, 0}, {1, 0} , // left
                {0, 1.0f}, {1.0f, 1.0f}, // back 
                {1.0f, 0.75f}, {0, 0.75f},  
                {0, 0.25}, {1.0f, 0.25},  // top
                {1.0f, 0.0f}, {0, 0.0f},
                {0, 1}, {1, 1}, {1, 0}, {0, 0} // right
              });
    setVelocity(5);
  }

  virtual void update(float dt) {
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    positionX -= velocityX * dt;
    left -= velocityX * dt;

    glPushMatrix();

    glTranslatef(positionX, 0.0f, 0.0f);

    glColor3fv(comm::color::WHITE);
    draw();

    glPopMatrix();
  }
};