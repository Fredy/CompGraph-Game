#include "common.hpp"
#include "mapReader.hpp"
#include "objects/player.hpp"
#include "objects/rectangle.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>
using namespace std;

GLuint WIDTH = 1280, HEIGHT = 720;

const float BLUE[] = {0.298f, 0.686f, 1.0f};
const float ORANGE[] = {1.0f, 0.67f, 0.0f};
const float RED[] = {0.81f, 0.02f, 0.0f};
const float BLACK[] = {0.0f, 0.0f, 0.0f};
const float WHITE[] = {1.0f, 1.0f, 1.0f, 1.0f};
const float GREEN[] = {0.1f, 1.0f, 0.2f};

Player character;

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  cout << "Width and height: " << width << ", " << height << "\n";
  WIDTH = width;
  HEIGHT = height;
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    character.startJump();
  }
  if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
    character.endJump();
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    character.startSlide();
    character.earlyEndJump();
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
    character.endSlide();
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
  glDisable(GL_COLOR_MATERIAL);

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

  Rectangle foreground(0, 0, comm::UNIT_WIDTH, 3, 2);
  Rectangle background(0, 0, comm::UNIT_WIDTH, comm::UNIT_HEIGHT, 90);

  MapReader mapReader({"maps/tst.map"});
  mapReader.load(0);

  /// TEXTURE ////
  stbi_set_flip_vertically_on_load(true);
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture
  // object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load("textures/floor.png", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    // glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture" << endl;
  }
  stbi_image_free(data);
  /// TEXTURE ////

  /// TEXTURE ////
  stbi_set_flip_vertically_on_load(true);
  GLuint texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping/filtering options (on the currently bound texture
  // object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // load and generate the texture
  data = stbi_load("textures/wall2.png", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    // glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture" << endl;
  }
  stbi_image_free(data);
  /// TEXTURE ////

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

    glColor4fv(WHITE);
    foreground.basicDraw(texture);

    glColor3fv(BLUE);
    background.basicDraw();

    character.draw(dt);

    mapReader.updateMap(dt, character);

    // drawGrid();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
