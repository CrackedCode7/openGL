#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
    public:
        Camera(float x, float y, float z, int SCR_WIDTH, int SCR_HEIGHT);

        glm::vec3 cameraPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::vec3 up;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;

        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 model;

        void recalculateMatrices();
        void setCameraPos(glm::vec3 cameraPos);
        void setCameraTarget(glm::vec3 cameraTarget);
        void setModelMatrix(glm::mat4 model);
};