#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera(float x, float y, float z, int SCR_WIDTH, int SCR_HEIGHT)
{
    cameraPos = glm::vec3(x, y, z);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    model = glm::mat4(1.0f);
    
    recalculateMatrices();
}


void Camera::recalculateMatrices()
{
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(cameraDirection, up));
    cameraUp = glm::cross(cameraRight, cameraDirection);

    view = glm::lookAt(cameraPos, cameraTarget, up);
}


void Camera::setCameraPos(glm::vec3 cameraPos)
{
    this -> cameraPos = cameraPos;
}


void Camera::setCameraTarget(glm::vec3 cameraTarget)
{
    this -> cameraTarget = cameraTarget;
}


void Camera::setModelMatrix(glm::mat4 model)
{
    this -> model = model;
}