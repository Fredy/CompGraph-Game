#include "helpers/shader.hpp"
#include "objects/object.hpp"
#include "objects/rectangle.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "objects/player.hpp"
using namespace std;

GLuint WIDTH = 1280, HEIGHT = 720;
float UNIT_WIDTH = 64.0f, UNIT_HEIGTH = 36.0f;

const float BLUE[] = {0.16f, 0.23f, 0.88f};
const float ORANGE[] = {1.0f, 0.67f, 0.0f};
const float RED[] = {0.81f, 0.02f, 0.0f};
const float BLACK[] = {0.0f, 0.0f, 0.0f};
const float GREEN[] = {0.1f, 1.0f, 0.2f};

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
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  return window;
}


void drawGizmo() {
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex3d(-UNIT_WIDTH, 0, 0);
	glVertex3d(UNIT_WIDTH, 0, 0);
	glColor3d(0, 255, 0);
	glVertex3d(0, -UNIT_HEIGTH, 0);
	glVertex3d(0, UNIT_HEIGTH, 0);
	glEnd();
}



int main() {
  GLFWwindow *window = initGL();
  if (!window) {
    return 1;
  }

  Rectangle foreground(0, 0, UNIT_WIDTH, 6, 2);
  Player character;

  Rectangle test (-8,-8,4,4, 3);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, UNIT_WIDTH, 0.0f, UNIT_HEIGTH, 0.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    drawGizmo();

    glColor3fv(GREEN);
    foreground.draw();

    character.draw(0.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}