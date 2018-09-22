#pragma once

#include "rectangle.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Player : public Rectangle {
private:
  using Rectangle::draw;
  
  float black[3] = {0.0f, 0.0f, 0.0f};

  GLuint uniColorId;
  GLuint uniMVPId;


  glm::mat4 fixPosition(bool isSliding = false) {
    glm::mat4 pos(1.0f);
    pos = glm::translate(pos, {9.0f, 9.0f, 0});
    return pos;

  }
public:
  Player(GLuint shaderId) : Rectangle(2.0f, 6.0f, 2.0f, shaderId) {
    uniMVPId = glGetUniformLocation(shaderId, "mvp");
    uniColorId = glGetUniformLocation(shaderId, "inColor");
  }


  void jump() {

  }

  void draw(glm::mat4 viewProjectionMat) {
    draw([&] {
      glm::mat4 mvp = viewProjectionMat * fixPosition();
      glUniform3fv(uniColorId, 1, black);
      glUniformMatrix4fv(uniMVPId, 1, GL_FALSE, &mvp[0][0]);
    });
    
  }
};