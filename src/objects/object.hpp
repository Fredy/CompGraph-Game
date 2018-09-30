#pragma once

#include <glad/glad.h>
#include <vector>
#include <array>
using namespace std;

class Object {
private:
  GLenum mode;
  vector<array<float, 3>> vertices;

public:
  void setData(const vector<array<float, 3>> &vertices, GLenum mode) {
    this->vertices = vertices;
    this->mode = mode;
  }

  void setMode(GLenum mode) { this->mode = mode; }

  void setVertices(const vector<array<float, 3>> &vertices) {
    this->vertices = vertices;
  }

  // This method shouldn't be used when drawing something that moves (or
  // anything). Use draw(deltaTime) instead.
  void draw() {
    glBegin(mode);
    for (const auto &vertex : vertices)  {
      glVertex3f(vertex[0], vertex[1], vertex[2]);
      // glVertex3fv(vertex.data());
    }
    glEnd();
  }

  virtual void draw(float dt);
};