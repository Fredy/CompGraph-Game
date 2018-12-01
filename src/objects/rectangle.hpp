#pragma once

#include "object.hpp"

class Rectangle : public Object {
private:
  using Object::setData;
  using Object::setMode;
  using Object::setVertices;

protected:
  float bottom;
  float left;
  float z;
  float width;
  float height;
  float sizeZ;

public:
  /* Draws the rectangle with it bottom left corner at (left, bottom) */
  Rectangle(float left, float bottom,  float z,float width, float height,float sizeZ) {
    this->left = left;
    this->bottom = bottom;
    this->z = z;
    this->width = width;
    this->height = height;
    this->sizeZ = sizeZ;

    vector<array<float, 3>> vertices = {
        // Front
        {left, bottom, z},
        {left + width, bottom , z},
        {left + width, bottom + height, z},
        {left, bottom + height, z},
        // Bottom
        {left, bottom, z},
        {left + width, bottom, z},
        {left + width, bottom, z + sizeZ},
        {left, bottom, z + sizeZ},
        // Left
        {left, bottom, z},
        {left, bottom, z + sizeZ},
        {left, bottom + height, z + sizeZ},
        {left, bottom + height, z},
        // Back
        {left, bottom, z + sizeZ},
        {left + width, bottom, z + sizeZ},
        {left + width, bottom + height, z + sizeZ},
        {left, bottom + height, z + sizeZ},
        // Top
        {left, bottom + height, z},
        {left + width, bottom + height, z},
        {left + width, bottom + height, z + sizeZ},
        {left, bottom + height, z + sizeZ},
        // Right
        {left + width, bottom, z},
        {left + width, bottom, z + sizeZ},
        {left + width, bottom + height, z + sizeZ},
        {left + width, bottom + height, z},
    };
    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0} , {0, 0}, {1, 0}, {1, 1}, {0, 1} ,
                  {1, 1}, {0, 1}, {0, 0}, {1, 0} , {0, 1}, {1, 1}, {1, 0}, {0, 0} ,
                  {0, 1}, {1, 1}, {1, 0}, {0, 0} , {0, 1}, {1, 1}, {1, 0}, {0, 0} });
    setData(vertices, GL_QUADS);
  }

  /* Draws the rectangle at (0, 0) */
  Rectangle(float width, float height,float sizeZ)
      : Rectangle(-width / 2.0f, -height / 2.0f, -sizeZ / 2.0f, width, height, sizeZ) {}

  virtual void update(float dt) {
    draw();
  };
};
