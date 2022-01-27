/* -----------------------------------------------------------------------------
	In this version I add a uniform to the vertex shader to allow us to pass in
	a transformation matrix (mat4 type). The gl_Position attribute uses this
	uniform to transform input vertices.

	We set the uniform value in the while loop. (I think attributes set before render loop,
	and uniforms can be set once the program is in use)

	GLM is used for the matrix math, and was added to the include folder.
   ----------------------------------------------------------------------------- */


#include <glad/glad.h> // before glfw (I think it HAS to be)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"


// Constant settings
// -----------------------------------------------------------------------------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// Whenever the window size changes this callback is executed
// -----------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Resize viewport to match new window size
	glViewport(0, 0, width, height);
}


// Function to query from GLFW whether keys were pressed, etc.
// -----------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	// Close window if ESC pressed
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

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
	float vertices[] = {
        -1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the VAO first, then bind and set VBO(s), then configure vertix attribute(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	// Render loop
	// -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
    {
        // input
		// ----------
        processInput(window);


		// render
		// ----------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	
		// New way to draw triangles using shader class
		ourShader.use();
		glBindVertexArray(VAO);
		// Transformation uniform in vertex shader setup
		glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.setMat4("transform", trans);
		glDrawArrays(GL_TRIANGLES, 0, 3);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// ----------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


	// Optionally de-allocate resources
	// -----------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteProgram(shaderProgram);
	

	// Terminate glfw before the program ends
	// -----------------------------------------------------------------------------
	glfwTerminate();

	return 0;
}