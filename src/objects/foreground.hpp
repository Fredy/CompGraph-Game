#pragma once

#include "obstacles/obstacle.hpp"
#include "common.hpp"

class Foreground : public Rectangle {
  private:
  void update(float dt) override {}
  float textureX = 0.0f;
public:

  // Rectangle floor1(-50,2, 2, 200, 1, 100, 0);
  // Rectangle floor2(-50,2,-10, 200, 1, 8, 0);

  //Background() : Rectangle(-12,2,-10, comm::UNIT_WIDTH * 2, comm::UNIT_HEIGHT, 1, 0) {
  Foreground(float z, float zSize) : Rectangle(-12, 2, z, comm::UNIT_WIDTH * 2, 1, zSize, 0) {
    setTextureId(texture::load(config::fgTexturePath));
  }

 bool checkCollision(float otherLeft, float otherBottom, float otherRight,
                      float otherTop) {
    // This only determines if there has been a collision, most times it can not
    // determine the position (direction) of the collision

    const float right = left + width;
    const float top = bottom + height;
    if (bottom <= otherTop and top >= otherBottom and left <= otherRight and
        right >= otherLeft) {
      return true;
    }

    return false;
  }

  virtual void update(float dt, const Player &player){
    // Everything that needs a tranformation must go inside glPushMatrix() and
    // glPopMatrix()
    textureX += 5.0f * dt / comm::UNIT_WIDTH;
    setTexCoords({});

    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} , // front
                  {0, 0}, {1, 0}, {1, 1}, {0, 1} , // bottom
                  {1, 1}, {0, 1}, {0, 0}, {1, 0} , // left
                  {textureX, 1.0f}, {1.0f + textureX, 1.0f}, // back 
                  {1.0f +textureX, 0.0f}, {textureX, 0.0f},  
{textureX, 1.0f}, {1.0f + textureX, 1.0f}, {1.0f +textureX, 0.0f}, {textureX, 0.0f},
                  {0, 1}, {1, 1}, {1, 0}, {0, 0} }); // right

    bool collision = checkCollision(player.getLeft(), player.getBottom(), player.getRight(),
                   player.getTop());
    if (collision) {
      player.setGround(0.0f);
    }
    draw();
  }
};
