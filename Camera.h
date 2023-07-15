#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

const float YAW{-90.0f};
const float PITCH{0.0f};
const float SPEED{2.5f};
const float SENSITIVITY{0.1f};
const float ZOOM{45.0f};

class Camera {
public:
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

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH)
      : front{glm::vec3(0.0f, 0.0f, -1.0f)},
        movementSpeed{SPEED},
        mouseSensitivity{SENSITIVITY},
        zoom{ZOOM} {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVector();
  }

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch)
      : front{glm::vec3(0.0f, 0.0f, -1.0f)},
        movementSpeed{SPEED},
        mouseSensitivity{SENSITIVITY},
        zoom{ZOOM} {
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVector();
  }

  glm::mat4 getViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
  }

  void processKeyboard(Camera_Movement direction, float deltaTime);

  void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

  void processMouseScroll(float yoffset);

private:
  void updateCameraVector() {
    glm::vec3 front{};
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
  }
};

