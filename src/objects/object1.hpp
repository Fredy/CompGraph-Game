#pragma once

#include <GLFW/glfw3.h>
class Object {
private:
  int numVertices;
  GLenum mode;

public:
  void setVerticesData(int numVertices) {
    this->numVertices = numVertices;
  }
  void setMode(GLenum mode) { this->mode = mode; }
};
