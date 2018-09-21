#pragma once

#include "object.hpp"

class Rectangle : public Object {
private:
  using Object::setExternalData;
  using Object::setMode;
  using Object::setVerticesData;

public:
  /* Draws the rectangle with it bottom left corner at (left, bottom) */
  Rectangle(float left, float bottom, float width, float height, float depth,
            GLuint shaderId) {
    GLfloat vertices[] = {
        left,         bottom,          -depth, // bl
        left + width, bottom,          -depth, // br
        left + width, bottom + height, -depth, // tr
        left,         bottom + height, -depth, // tl
    };
    GLuint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };
    setVerticesData(4, vertices, 6, indices);
    setMode(GL_TRIANGLES);
    setShader(shaderId);
  }

  /* Draws the rectangle at (0, 0) */
  Rectangle(float width, float height, float depth, GLuint shaderId) {
    float left = -width / 2.0f;
    float bottom = -height / 2.0f;
    Rectangle(left, bottom, width, height, depth, shaderId);
  }
};
