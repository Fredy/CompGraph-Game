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
  Rectangle(float left, float bottom,  float z,float width, float height,float sizeZ, float depth) {
    this->left = left;
    this->bottom = bottom;
    this->z = z;
    this->width = width;
    this->height = height;
    this->sizeZ = sizeZ;

    vector<array<float, 3>> vertices = {

        {left, bottom, z},
        {left + width, bottom , z},
        {left + width, bottom + height, z},
        {left, bottom + height, z},

        {left, bottom, z},
        {left + width, bottom, z},
        {left + width, bottom, z + sizeZ},
        {left, bottom, z + sizeZ},

        {left, bottom, z},
        {left, bottom, z + sizeZ},
        {left, bottom + height, z + sizeZ},
        {left, bottom + height, z},

        {left, bottom, z + sizeZ},
        {left + width, bottom, z + sizeZ},
        {left + width, bottom + height, z + sizeZ},
        {left, bottom + height, z + sizeZ},

        {left, bottom + height, z},
        {left + width, bottom + height, z},
        {left + width, bottom + height, z + sizeZ},
        {left, bottom + height, z + sizeZ},

        {left + width, bottom, z},
        {left + width, bottom, z + sizeZ},
        {left + width, bottom + height, z + sizeZ},
        {left + width, bottom + height, z},
        
        /*{left, bottom, -depth},                  // bl
        {left + width, bottom, -depth},          // br
        {left + width, bottom + height, -depth}, // tr
        {left, bottom + height, -depth},         // tl*/
    };
    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0}});
    setData(vertices, GL_QUADS);
  }

  /* Draws the rectangle at (0, 0) */
  Rectangle(float width, float height,float sizeZ, float depth)
      : Rectangle(-width / 2.0f, -height / 2.0f, -sizeZ / 2.0f, width, height, sizeZ, depth) {}
};
