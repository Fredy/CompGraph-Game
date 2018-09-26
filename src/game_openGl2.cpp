#include "objects/object.hpp"
#include "objects/rectangle.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
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

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(640, 480, "game runner", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    cout << "hola" << endl;
  Rectangle foreground(0,0,UNIT_WIDTH,6, 1);
  Rectangle character(8,6,2,6, 0);
    cout << "hola" << endl;

  glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  while (!glfwWindowShouldClose(window))
  {
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
  glfwDestroyWindow(window);
  glfwTerminate();     
  exit(EXIT_SUCCESS);
  return 1;
}
