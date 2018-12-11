#pragma once

#include "obstacles/obstacle.hpp"
#include "common.hpp"

class Foreground : public Rectangle {
  private:
  void update(float dt) override {}
  float textureX = 0.0f;
public:

  Foreground(float z, float zSize) : Rectangle(-12, 0, z, comm::UNIT_WIDTH * 2, 3, zSize) {
    setTextureId(texture::load(config::fgTexturePath));
  }

 bool checkCollision(float otherBottom, float otherTop) {
    // This only checks vertical collision. 
    const float top = bottom + height;
    return (bottom <= otherTop and top >= otherBottom );
  }

  virtual void update(float dt, const Player &player){
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    textureX += 5.0f * dt / comm::UNIT_WIDTH;
    setTexCoords({});


    // NOTE: the constant 2.0 is from the  comm::UNIT_WIDTH * 2, 3.0 if from width.
    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} , // front
                  {0, 0}, {1, 0}, {1, 1}, {0, 1} , // bottom
                  {1, 1}, {0, 1}, {0, 0}, {1, 0} , // left
                  {textureX, 1.0f}, {2.0f + textureX, 1.0f}, // back 
                  {2.0f + textureX, 0.75f}, {textureX, 0.75f},  
                  {textureX, 0.75}, {2.0f + textureX, 0.75},  // top
                  {2.0f +textureX, 0.0f}, {textureX, 0.0f},
                  {0, 1}, {1, 1}, {1, 0}, {0, 0} // right
                });

    bool collision = checkCollision(player.getBottom(), player.getTop());
    if (collision) {
      player.setGround(0.0f);
    }
    draw();
  }
};
