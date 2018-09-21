#include "helpers/shader.hpp"
#include "objects/object.hpp"
#include "objects/rectangle.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;

GLuint WIDTH = 1280, HEIGHT = 720;
float UNIT_WIDTH = 64.0f, UNIT_HEIGTH = 36.0f;

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  cout << "Width and height: " << width << ", " << height << "\n";
  WIDTH = width;
  HEIGHT = height;
  glViewport(0, 0, width, height);
}

GLFWwindow *initGL() {
  // GLFW initialization
  if (!glfwInit()) {
    cout << "GLFW initialization failed\n";
    glfwTerminate();
    return nullptr;
  }

  // GLFW setup
  glfwWindowHint(GLFW_SAMPLES, 4); // Anti aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Test window", nullptr, nullptr);
  if (!window) {
    cout << "GLFW windows creation failed failed\n";
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  // Glad initialization
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD\n";
    return nullptr;
  }
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);

  return window;
}

int main() {
  GLFWwindow *window = initGL();
  if (!window) {
    return 1;
  }

  // Build and compile shader programs.
  Shader shaders("shaders/example_v.glsl", "shaders/example_f.glsl");

  Rectangle foreground(0,0,UNIT_WIDTH,6, 1, shaders.ID);
  Rectangle character(8,6,2,6, 0, shaders.ID);

  float blue[3] = {0.16f, 0.23f, 0.88f};
  float orange[3] = {1.0f, 0.67f, 0.0f};
  float red[3] = {0.81f, 0.02f, 0.0f};
  float black[3] = {0.0f, 0.0f, 0.0f};
  float green[3] = {0.1f, 1.0f, 0.2f};
  
  // MVP
  glm::mat4 projectionMat = glm::ortho(0.0f, UNIT_WIDTH, 0.0f, UNIT_HEIGTH, 0.0f,
                                       100.0f); // In world coordinates


  glm::mat4 viewMat =
      glm::lookAt(glm::vec3{0,0,1}, {0,0,0}, {0, 1, 0});

  glm::mat4 modelMat = glm::mat4(1.0f);


  glm::mat4 mvp = projectionMat * viewMat * modelMat;
  GLuint matrixId = glGetUniformLocation(shaders.ID, "mvp");
  GLint colorId = glGetUniformLocation(shaders.ID, "inColor");

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    foreground.draw([&] {
      glUniform3fv(colorId, 1, green);
      glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
    });

    character.draw([&] {
      glUniform3fv(colorId, 1, black);
      glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
    });

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  foreground.destroy();
  character.destroy();

  glfwTerminate();
}