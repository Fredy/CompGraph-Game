#include "camera.hpp"

Camera::Camera(GLFWwindow *window, float speed, float mouseSpeed) {
  this->window = window;
  this->speed = speed;
  this->mouseSpeed = mouseSpeed;

  eyeArray[0] = glm::vec3(1.75122, 13.2589, 15.2102);
  eyeArray[1] = glm::vec3(5.67806, 15.7585, 14.6789);
  eyeArray[2] = glm::vec3(1.93349, 14.6635, 17.2827);
  eyeArray[3] = glm::vec3(0.618218, 17.2819, 20.5883);

  centerArray[0] = glm::vec3(2.16641, 12.8848, 14.3809);
  centerArray[1] = glm::vec3(6.04087, 15.2914, 13.8726);
  centerArray[2] = glm::vec3(2.15253, 14.2108, 16.4184);
  centerArray[3] = glm::vec3(0.954903, 16.8389, 19.7575);

  upArray[0] = glm::vec3(0.104605, 0.912315, -0.359178);
  upArray[1] = glm::vec3(0.12414, 0.873726, -0.450302);
  upArray[2] = glm::vec3(0.0822022, 0.889705, -0.445174);
  upArray[3] = glm::vec3(0.0945107, 0.883503, -0.432802);

  viewMatrix = glm::lookAt(eyeArray[0], centerArray[0], upArray[0]);
}

void Camera::computeMatrices(float dt) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  projectionMatrix = glm::perspective(glm::radians(45.0f),
                                      float(width) / height, 0.1f, 100000.0f);
  // freeCamera(dt); // NOTE: For debugging.
  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    viewMatrix = glm::lookAt(eyeArray[0], centerArray[0], upArray[0]);
  }
  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
    viewMatrix = glm::lookAt(eyeArray[1], centerArray[1], upArray[1]);
  }
  if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
    viewMatrix = glm::lookAt(eyeArray[2], centerArray[2], upArray[2]);
  }
  if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
    viewMatrix = glm::lookAt(eyeArray[3], centerArray[3], upArray[3]);
  }
}

void Camera::freeCamera(float dt) {

  // Get mouse position
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  // Reset mouse position for next frame
  glfwSetCursorPos(window, width / 2.0, height / 2.0);

  // Compute new orientation
  horizontalAngle += mouseSpeed * float(width / 2.0 - xpos);
  verticalAngle += mouseSpeed * float(height / 2.0 - ypos);

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                      sin(verticalAngle),
                      cos(verticalAngle) * cos(horizontalAngle));

  // Right vector
  glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0,
                              cos(horizontalAngle - 3.14f / 2.0f));

  // Up vector
  glm::vec3 up = glm::cross(right, direction);

  // Speed multiplier
  float mult = 1.0f;
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    mult = 0.15f;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    mult = 3.0f;
  }

  // Move forward
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    position += direction * dt * speed * mult;
  }
  // Move backward
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    position -= direction * dt * speed * mult;
  }
  // Strafe right
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    position += right * dt * speed * mult;
  }
  // Strafe left
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    position -= right * dt * speed * mult;
  }

  projectionMatrix = glm::perspective(glm::radians(45.0f),
                                      float(width) / height, 0.1f, 100000.0f);
  viewMatrix = glm::lookAt(position, position + direction, up);
}