#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
  Camera(glm::vec3 position);

  glm::mat4 getViewMatrix();
  float getZoom();
  glm::vec3 getPosition();
  bool isActive();

  void processKeyboard(Camera_Movement direction, float deltaTime);
  void processMouseMovement(float xpos, float ypos);
  void processMouseScroll(float yoffset);
  void toggle();

private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;

  float yaw;
  float pitch;

  float movementSpeed;
  float mouseSensitivity;
  float zoom;

  bool firstMouse;
  float lastX;
  float lastY;

  bool active;

  void updateCameraVectors();
};
