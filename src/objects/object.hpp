#pragma once

#include <array>
#include <glad/glad.h>
#include <vector>
#include "helpers/texture.hpp"
#include "config.hpp"
using namespace std;

class Object {
private:
  GLenum mode;
  GLuint textureId = 0;
  vector<array<float, 3>> vertices;
  vector<array<float, 2>> texCoords;

protected:
  // This method shouldn't be used when drawing something that moves (or
  // anything). Use draw(deltaTime) instead.
  void draw() {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(mode);
    for (size_t i = 0; i < vertices.size(); i++) {
      glTexCoord2fv(texCoords[i].data());
      glVertex3fv(vertices[i].data());
    }
    glEnd();
    // unbind texture is not neccesary, if you want to draw an object without
    // texture pass 0 or nothing as parameter
  }

  void setData(const vector<array<float, 3>> &vertices, GLenum mode) {
    this->vertices = vertices;
    this->mode = mode;
    if (texCoords.size() == 0) {
      for (const auto &vertex : vertices) {
        texCoords.push_back({vertex[0], vertex[1]});
      }
    }
  }

  void setMode(GLenum mode) { this->mode = mode; }

  void setTextureId(GLuint textureID) { this->textureId = textureID; }
  void setVertices(const vector<array<float, 3>> &vertices) {
    this->vertices = vertices;
  }

  void setTexCoords(const vector<array<float, 2>> &texCoords) {
    this->texCoords = texCoords;
  }

public:
  virtual void update(float dt) = 0;
};