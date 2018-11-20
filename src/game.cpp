#include "common.hpp"
#include "mapReader.hpp"
#include "objects/player.hpp"
#include "objects/rectangle.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
#include "helpers/texture.hpp"
#include "objects/foreground.hpp"
#include "objects/background.hpp"
using namespace std;

GLuint WIDTH = 1280, HEIGHT = 720;

Player player;

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  cout << "Width and height: " << width << ", " << height << "\n";
  WIDTH = width;
  HEIGHT = height;
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    player.startJump();
  }
  if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
    player.endJump();
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    player.startSlide();
    player.earlyEndJump();
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
    player.endSlide();
  }
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
  glfwSetKeyCallback(window, keyCallback);

  // Glad initialization
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD\n";
    return nullptr;
  }
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
//  glDisable(GL_COLOR_MATERIAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);


  return window;
}

void drawGizmo() {
  glBegin(GL_LINES);
  glColor3d(255, 0, 0);
  glVertex3d(-comm::UNIT_WIDTH, 0, 0);
  glVertex3d(comm::UNIT_WIDTH, 0, 0);
  glColor3d(0, 255, 0);
  glVertex3d(0, -comm::UNIT_HEIGHT, 0);
  glVertex3d(0, comm::UNIT_HEIGHT, 0);
  glEnd();
}

void drawGrid() {
  glBegin(GL_LINES);
  glColor3f(1, 1, 1);
  for (int i = 0; i <= comm::UNIT_WIDTH; i++) {
    glVertex3f(i, 0, 0);
    glVertex3f(i, comm::UNIT_HEIGHT, 0);
  }

  for (int i = 0; i <= comm::UNIT_HEIGHT; i++) {
    glVertex3f(0, i, 0);
    glVertex3f(comm::UNIT_WIDTH, i, 0);
  }
  glEnd();
}

int main() {
  GLFWwindow *window = initGL();
  if (!window) {
    return 1;
  }

  Foreground foreground;
  Background background;

  MapReader mapReader({"maps/one.map", "maps/two.map", "maps/three.map"});
  mapReader.load(2);

  double dt, currentTime, lastTime = 0.0;
  // Main loop
  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    dt = currentTime - lastTime;
    lastTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, comm::UNIT_WIDTH, 0.0f, comm::UNIT_HEIGHT, 0.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    player.update(dt);
    glColor3fv(comm::color::WHITE);
    foreground.update(dt, player);

    background.update(dt);


    mapReader.updateMap(dt, player);

    //  drawGrid();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
