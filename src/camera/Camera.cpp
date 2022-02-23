#include "Camera.h"

#include "VectorRotation.h" // rotate_vec3

#include <glad/glad.h> // before glfw (I think it HAS to be)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp> // glm::to_string(mat) for matrix printing


Camera::Camera(float x, float y, float z, int SCR_WIDTH, int SCR_HEIGHT)
{
    this -> SCR_WIDTH = SCR_WIDTH;
    this -> SCR_HEIGHT = SCR_HEIGHT;

    cameraPos = glm::vec3(x, y, z);
    cameraTarget = glm::vec3(x, y, z+1.0f);
    
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
    model = glm::mat4(1.0f);
    
    recalculateMatrices();
}


void Camera::recalculateMatrices()
{
    cameraDirection = glm::normalize(cameraTarget - cameraPos);
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


void Camera::handleInput(GLFWwindow* window)
{
    // Check movement keys (WASD, LCTRL, SPACE)
	// -----------------------------------------------------------------------------
	// bool to decide whether we need to re-calculate matrices
	bool recalculate = false;

	// Translation speed
	float transSpeed = 1;

	// W key
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		setCameraPos(cameraPos + glm::vec3(transSpeed * cameraDirection[0], 
										   0,
										   transSpeed * cameraDirection[2]));
		setCameraTarget(cameraTarget + glm::vec3(transSpeed * cameraDirection[0], 
												 0,
												 transSpeed * cameraDirection[2]));
		recalculate = true;
	}
	// A key
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		setCameraPos(cameraPos - glm::vec3(transSpeed * cameraRight[0],
										   0,
										   transSpeed * cameraRight[2]));
		setCameraTarget(cameraTarget - glm::vec3(transSpeed * cameraRight[0],
												 0,
												 transSpeed * cameraRight[2]));
		recalculate = true;
	}
	// S key
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		setCameraPos(cameraPos - glm::vec3(transSpeed * cameraDirection[0], 
										   0,
										   transSpeed * cameraDirection[2]));
		setCameraTarget(cameraTarget - glm::vec3(transSpeed * cameraDirection[0], 
												 0,
												 transSpeed * cameraDirection[2]));
		recalculate = true;
	}
	// D key
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		setCameraPos(cameraPos + glm::vec3(transSpeed * cameraRight[0],
										   0,
										   transSpeed * cameraRight[2]));
		setCameraTarget(cameraTarget + glm::vec3(transSpeed * cameraRight[0],
												 0,
												 transSpeed * cameraRight[2]));
		recalculate = true;
	}
	// Space bar
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		setCameraPos(cameraPos + transSpeed * up);
		setCameraTarget(cameraTarget + transSpeed * up);
		recalculate = true;
	}
	// Left control
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		setCameraPos(cameraPos - transSpeed * up);
		setCameraTarget(cameraTarget - transSpeed * up);
		recalculate = true;
	}


    // Re-calculate camera matrices if required
	// -----------------------------------------------------------------------------
	if (recalculate)
	{
		recalculateMatrices();
	}


    // Check for rotation
	// -----------------------------------------------------------------------------
	
	// Check mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	// Get window size (in case we resized)
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	
	// Check whether cursor no longer in center (need to rotate)
	// X direction
	if (floor(xpos) != floor(width/2.0))
	{
        float difference = floor(xpos) - floor(width/2.0);
        glm::vec3 res = rotate_vec3(cameraDirection, up, -0.1f*difference);
        cameraDirection = res;
        cameraTarget = cameraPos + cameraDirection;
	
		recalculate = true;
	}
    // Y direction
	if (floor(ypos) != floor(height/2.0))
	{
		float difference = floor(ypos) - floor(height/2.0);
        glm::vec3 res = rotate_vec3(cameraDirection, cameraRight, -0.1f*difference);
        cameraDirection = res;
        cameraTarget = cameraPos + cameraDirection;
	
		recalculate = true;
	}
	
	// Set cursor back to middle of window
	glfwSetCursorPos(window, width/2.0, height/2.0);


	// Re-calculate camera matrices if required
	// -----------------------------------------------------------------------------
	if (recalculate)
	{
		recalculateMatrices();
	}
}