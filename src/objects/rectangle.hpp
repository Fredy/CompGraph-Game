#pragma once

#include "object.hpp"

class Rectangle : public Object {
private:
  using Object::setMode;
  using Object::setData;
  using Object::setVertices;

public:
  /* Draws the rectangle with it bottom left corner at (left, bottom) */
  Rectangle(float left, float bottom, float width, float height, float depth) {
    vector<array<float,3>> vertices= {
        {left,         bottom,          -depth}, // bl
        {left + width, bottom,          -depth}, // br
        {left + width, bottom + height, -depth}, // tr
        {left,         bottom + height, -depth}, // tl
    };
    setData(vertices, GL_QUADS);
  }

  /* Draws the rectangle at (0, 0) */
  Rectangle(float width, float height, float depth) {
    float left = -width / 2.0f;
    float bottom = -height / 2.0f;
    Rectangle(left, bottom, width, height, depth);
  }
};
