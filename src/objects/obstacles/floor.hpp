#pragma once

#include "obstacle.hpp"
class Floor : public Obstacle {
private:
  void setRandomTexCoords() {
    using namespace comm::rndTex;
    vector<array<float, 2>> coords;
    coords.reserve(24); // 6 faces * 4 coords
    // Front, bottom, left, back
    for (int i = 0; i < 4; i++) {
      const auto &tmp = texPositions[randomDist(generator)];
      coords.insert(coords.end(), tmp.begin(), tmp.end());
    }
    // Top
    auto tmp = genTexPositions(1, sizeZ)[randomDist(generator) > 1? 1: 3];
    coords.insert(coords.end(), tmp.begin(), tmp.end());
    // Right
    tmp = texPositions[randomDist(generator)];
    coords.insert(coords.end(), tmp.begin(), tmp.end());
    setTexCoords(coords);
  }

public:
  Floor(float left, float bottom, float depth = 3.0f)
      : Obstacle(left, bottom, 0, depth) {
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

// setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} ,
// {0, 0}, {1, 0}, {1, 1}, {0, 1} ,
//               {1, 1}, {0, 1}, {0, 0}, {1, 0} ,
//                {0, 1}, {1, 1}, {1, 0}, {0, 0} ,
//               {0, 1}, {1, 1}, {1, 0}, {0, 0} ,
//               {0, 1}, {1, 1}, {1, 0}, {0, 0} });