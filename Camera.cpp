#include "Camera.h"

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = this->movementSpeed * deltaTime;
  if (direction == Camera_Movement::FORWARD) {
    this->position += this->front * velocity;
  } else if (direction == Camera_Movement::BACKWARD) {
    this->position -= this->front * velocity;
  } else if (direction == Camera_Movement::LEFT) {
    this->position -= this->right * velocity;
  } else if (direction == Camera_Movement::RIGHT) {
    this->position += this->right * velocity;
  }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
  xoffset *= this->mouseSensitivity;
  yoffset *= this->mouseSensitivity;
  this->yaw += xoffset;
  this->pitch += yoffset;

  if (constrainPitch) {
    if (this->pitch > 89.0f) {
      this->pitch = 89.0f;
    }
    if (this->pitch < -89.0f) {
      this->pitch = -89.0;
    }
  }

  updateCameraVector();
}

void Camera::processMouseScroll(float yoffset) {
  this->zoom -= yoffset;
  if (this->zoom < 1.0f) {
    this->zoom = 1.0f;
  }
  if (this->zoom > 45.0f) {
    this->zoom = 45.0f;
  }
}
