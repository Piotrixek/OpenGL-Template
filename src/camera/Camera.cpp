#include "Camera.h"

Camera::Camera(glm::vec3 position)
    : position(position), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0f),
      pitch(0.0f), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f),
      mouseSensitivity(0.1f), zoom(45.0f), firstMouse(true), lastX(0.0f),
      lastY(0.0f), active(true) {
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position, position + front, up);
}

float Camera::getZoom() { return zoom; }

glm::vec3 Camera::getPosition() { return position; }

bool Camera::isActive() { return active; }

void Camera::toggle() {
  active = !active;
  firstMouse = true;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  if (direction == FORWARD)
    position += front * velocity;
  if (direction == BACKWARD)
    position -= front * velocity;
  if (direction == LEFT)
    position -= right * velocity;
  if (direction == RIGHT)
    position += right * velocity;
}

void Camera::processMouseMovement(float xpos, float ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
  zoom -= yoffset;
  if (zoom < 1.0f)
    zoom = 1.0f;
  if (zoom > 45.0f)
    zoom = 45.0f;
}

void Camera::updateCameraVectors() {
  glm::vec3 new_front;
  new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  new_front.y = sin(glm::radians(pitch));
  new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(new_front);
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}
