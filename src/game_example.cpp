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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
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
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  return window;
}

int main() {
  GLFWwindow *window = initGL();
  if (!window) {
    return 1;
  }

  Rectangle foreground(0,0,UNIT_WIDTH,6, 1);
  Rectangle character(8,6,2,6, 0);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(0.0f, UNIT_WIDTH, 0.0f, UNIT_HEIGTH, 0.0f,100.0f);        
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     foreground.draw();
    glColor3f(0.0,0.0,1.0); //TODO: pass color to the object class
    character.draw();
    glColor3f(0.0,1.0,0.0); //TODO: pass color to the object class

    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glfwTerminate();
}