#pragma once

#include <GLFW/glfw3.h>


namespace window
{
    extern unsigned int SCR_WIDTH;
    extern unsigned int SCR_HEIGHT;

    // Whenever the window size changes this callback is executed
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    // Function to query from GLFW whether keys were pressed, etc.
    void processInput(GLFWwindow* window);

    // Initialize GLFW
    bool initializeGLFW();

    // Create window
    GLFWwindow* createWindow();
}