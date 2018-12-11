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
#include "objects/initialFloor.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helpers/camera.hpp"
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
  if (key == GLFW_KEY_ESCAPE){
   		exit(1);
    }
}
template <typename Functor> void draw2D(Functor &&function) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, comm::UNIT_WIDTH, 0.0f, comm::UNIT_HEIGHT, -1000.0f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glBegin(GL_TRIANGLES);
  glColor3f(255,0,0);
  glVertex3f(100,100,0);
  glVertex3f(50,200,0);
  glVertex3f(0,100,0);
  glEnd();

  function();
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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    glVertex3f(i, comm::UNIT_HEIGHT, -50);
  }

  for (int i = 0; i <= comm::UNIT_HEIGHT; i++) {
    glVertex3f(0, i, 0);
    glVertex3f(comm::UNIT_WIDTH, i, -50);
  }
  glEnd();
}

int main() {
  GLFWwindow *window = initGL();
  if (!window) {
    return 1;
  }

  Foreground foregroundL(-9, 9);
  Foreground foregroundR(3, 9);
  InitialFloor initialFloor(0,0);

  Background background;

  MapReader mapReader({"maps/one.map", "maps/two.map", "maps/three.map"});
  mapReader.load(2);

  Camera camera(window, 20.0f, 0.0018f);
  glm::mat4 projectionMatrix = glm::perspective(
      glm::radians(45.0f), float(WIDTH) / HEIGHT, 0.1f, 1000.0f);

  glm::mat4 viewMatrix =
      glm::lookAt(glm::vec3(15.0f, 15.0f, 20.0f), {0, 0, 0}, {0, 1, 0});

  double dt, currentTime, lastTime = 0.0;
  // Main loop
  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    dt = currentTime - lastTime;
    lastTime = currentTime;

    camera.computeMatrices(dt);
    player.handleKeyInput(window);

    // 2D
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, comm::UNIT_WIDTH, 0.0f, comm::UNIT_HEIGHT, 0.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    mapReader.drawProgressBar(dt);

    // 3D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(&camera.getProjectionMatrix()[0][0]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(&camera.getViewMatrix()[0][0]);

    player.update(dt);
    glColor3fv(comm::color::WHITE);
    foregroundL.update(dt, player);
    // foregroundR.update(dt, player);
    initialFloor.update(dt);
    background.update(dt);

    glColor3f(0, 0.8f, 0.1f);

    mapReader.updateMap(dt, player);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
