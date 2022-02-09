/* -----------------------------------------------------------------------------
	In this version I add a ticking system to the mix. I moved the process input
	code to the ticking function so input (movement in this case) only processes
	at 60 fps. I also added up/down movement.
   ----------------------------------------------------------------------------- */


#include <glad/glad.h> // before glfw (I think it HAS to be)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp> // glm::to_string(mat) for matrix printing

#include <iostream>
#include <vector>
#include <cmath> // floor

#include "Shader.h"
#include "Cube.h"
#include "Camera.h"


// Constant settings
// ---------------------------------------------------------------------------------
const unsigned int SCR_WIDTH = 300;
const unsigned int SCR_HEIGHT = 300;


// Whenever the window size changes this callback is executed
// ---------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Resize viewport to match new window size
	glViewport(0, 0, width, height);
}


// Function to query from GLFW whether keys were pressed, etc.
// ---------------------------------------------------------------------------------
void processInput(GLFWwindow* window, Camera& camera)
{
	// Close window if ESC pressed
	// -----------------------------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main()
{
	// Initialize GLFW
	// -----------------------------------------------------------------------------
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	

	// Set up correct versions
	// -----------------------------------------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	// Create glfw Window
	// -----------------------------------------------------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwMakeContextCurrent(window); // Make new window current
	glfwSwapInterval(0); // No V-sync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, SCR_WIDTH/2.0, SCR_HEIGHT/2.0); // cursor in middle
	

	// Initialize GLAD
	// -----------------------------------------------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


	// New shader class implemented
	// -----------------------------------------------------------------------------
	Shader ourShader("shader.vs", "shader.fs");


	// Set up vertex data, vertex buffers, vertex arrays
	// -----------------------------------------------------------------------------
	Cube cube = Cube(0, 0, 0);
	std::vector<float> colors = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	
	// Generate Arrays and Buffers
	unsigned int VBO1, VBO2, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);

	// Bind the VAO first, then bind and set VBO(s), then configure vertex attribute(s)
	glBindVertexArray(VAO);

	// Bind VBO and EBO and set up buffer data (vertices in this case)
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(float), &cube.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indices.size() * sizeof(unsigned int), &cube.indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	

	// Unbind. Since VBO now unbound, we cannot set up vertex attributes.
	// A VAO and VBO MUST be bound to use glVertexAttribPointer
	// The VAO must be re-bound before drawing, and the shader activated
	// for calls like glDrawArrays to work.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	
	// Set up initial camera position, look at, and up vectors
	// Set up perspective projection, view, and model matrices
	// -----------------------------------------------------------------------------
	Camera camera(0.0f, 0.0f, 5.0f, SCR_WIDTH, SCR_HEIGHT);


	// OpenGL setup functions
	// -----------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	

	// Render loop
	// -----------------------------------------------------------------------------
	// Framerate variables
	double previousTime = glfwGetTime();
	double previousTickTime = glfwGetTime();
	double tickTime = 1.0/60.0;
	int frameCount = 0;
	int tickCount = 0;

	// Main loop
	while (!glfwWindowShouldClose(window))
    {
		// Framerate counting/displaying
		// -------------------------------------------------------------------------
		double currentTime = glfwGetTime();
		
		// Increment number of frames
		frameCount++;
		
		// Output frames and ticks once per second
		if (currentTime - previousTime >= 1.0)
		{
			std::cout << tickCount << " ticks " << frameCount << " fps" << std::endl;

			frameCount = 0;
			tickCount = 0;
			previousTime = currentTime;
		}
		
		// Ticking system
		// -------------------------------------------------------------------------
		// Try to tick 60 times per second
		if (currentTime - previousTickTime >= tickTime)
		{
			// input
			// ---------------------------------------------------------------------
			processInput(window, camera);


			// Camera input handling
			// ---------------------------------------------------------------------
			camera.handleInput(window);
			

			tickCount++;
			previousTickTime = currentTime;
		}
		

		// render
		// -------------------------------------------------------------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// New way to draw triangles using shader class
		ourShader.use();
		// First have to bind vertex array object to tell the shader what 
		// the vertex attributes look like
		glBindVertexArray(VAO);
		// Setup uniforms in vertex shader
		ourShader.setMat4("model", camera.model);
		ourShader.setMat4("view", camera.view);
		ourShader.setMat4("projection", camera.projection);
		// Draw (now with indexed vertices)
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


	// Optionally de-allocate resources
	// -----------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
	

	// Terminate glfw before the program ends
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}