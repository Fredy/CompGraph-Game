#pragma once

#include "object.hpp"

class Rectangle : public Object {
private:
  using Object::setData;
  using Object::setMode;
  using Object::setTexCoords;
  using Object::setVertices;

public:
  using Object::basicDraw;
  /* Draws the rectangle with it bottom left corner at (left, bottom) */
  Rectangle(float left, float bottom, float width, float height, float depth) {
    vector<array<float, 3>> vertices = {
        {left, bottom, -depth},                  // bl
        {left + width, bottom, -depth},          // br
        {left + width, bottom + height, -depth}, // tr
        {left, bottom + height, -depth},         // tl
    };
    setData(vertices, GL_QUADS);
    setTexCoords({{0, 1}, {1, 1}, {1, 0}, {0, 0}});
  }

  /* Draws the rectangle at (0, 0) */
  Rectangle(float width, float height, float depth)
      : Rectangle(-width / 2.0f, -height / 2.0f, width, height, depth) {}
};
