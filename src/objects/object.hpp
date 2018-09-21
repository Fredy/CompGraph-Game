#pragma once

#include <glad/glad.h>

class Object {
private:
  int numVertices;
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  GLuint shaderId;
  GLenum mode;

public:
  void setVerticesData(int verticesSize, const GLvoid *vertices, int indicesSize,
                       const GLvoid *indices) {
    this->numVertices = indicesSize;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    // Points
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * verticesSize * sizeof(GLfloat), vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices,
                 GL_STATIC_DRAW);

    // Unbind
    // Don't unbind the EBO while a VAO is active as the bound element buffer
    // object is stored in the VAO; keep the EBO bound.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void setShader(GLuint shaderId) { this->shaderId = shaderId; }

  void setMode(GLenum mode) { this->mode = mode; }

  template <typename Functor> void draw(Functor &&mvpModifications) {
    glUseProgram(shaderId);
    glBindVertexArray(vao);
    mvpModifications();
    glDrawElements(mode, numVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
  }

  void destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
  }

  void setExternalData(GLuint vao, GLuint vbo, GLuint ebo, int numVertices) {
    this->vao = vao;
    this->vbo = vbo;
    this->ebo = ebo;
    this->numVertices = numVertices;
  }
};