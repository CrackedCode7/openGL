#include "windowSetup.h"

#include <iostream>
#include <GLFW/glfw3.h>


unsigned int window::SCR_WIDTH = 800;
unsigned int window::SCR_HEIGHT = 450;


void window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Resize viewport to match new window size
	glViewport(0, 0, width, height);
}


void window::processInput(GLFWwindow* window)
{
    // Close window if ESC pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	

	// Toggle wireframe mode
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		int polygonMode;
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

		if (polygonMode == GL_LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (polygonMode == GL_FILL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
}


bool window::initializeGLFW()
{
    // Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

    // Set up versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}


GLFWwindow* window::createWindow()
{
    // Create glfw Window
	GLFWwindow* window = glfwCreateWindow(window::SCR_WIDTH, window::SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
	glfwMakeContextCurrent(window); // Make new window current
	glfwSwapInterval(0); // No V-sync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, SCR_WIDTH/2.0, SCR_HEIGHT/2.0); // cursor in middle

    return window;
}