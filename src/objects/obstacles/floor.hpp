#pragma once

#include "obstacle.hpp"
class Floor : public Obstacle {
private:
  void setRandomTexCoords() {
    using namespace comm::rndTex;

    auto tmp = genTexPositions(sizeZ, 1)[randomDist(generator) > 1? 0: 2];
    tmp[0] = {tmp[0][0], tmp[0][1] * 0.25f};
    tmp[1] = {tmp[1][0], tmp[1][1] * 0.25f};
    tmp[2] = {tmp[2][0], tmp[2][1] * 0.25f};
    tmp[3] = {tmp[3][0], tmp[3][1] * 0.25f};
    const vector<array<float, 2>> coords = {
      // Front
      {0, 1}, {1, 1}, {1, 0.25}, {0, 0.25}, 
      // Bottom
      tmp[0], tmp[1], tmp[2], tmp[3], 
      // Left
      {3, 1}, {0, 1}, {0, 0.25}, {3, 0.25}, 
      // Back
      {0, 1}, {1, 1}, {1, 0.25}, {0, 0.25},
      // Top
      tmp[0], tmp[1], tmp[2], tmp[3], 
      // Righ
      {0, 1}, {3, 1}, {3, 0.25}, {0, 0.25}
    };
    setTexCoords(coords);
  }

public:
  Floor(float left, float bottom, float depth = 3)
      : Obstacle(left, bottom - 2, 0, 1, 3, depth) {
    setTextureId(texture::load(config::fgSqrTexturePath));
    setRandomTexCoords();
  }

  virtual void update(float dt, const Player &player) {
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
