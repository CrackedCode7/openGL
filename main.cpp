/* -----------------------------------------------------------------------------
	In this version I added a shader for UI objects to render over 3D elements.
	Use the UI shader for this, which is after the 3D shader. For now I have
	not developed any UI objects that are useful, but these will be easy to add
	once I create textures for text.
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
#include "text.h"
#include "twoDimensionalObject.h"

#include "stb_image.h"


// Constant settings
// ---------------------------------------------------------------------------------
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;


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


	// Shaders
	// -----------------------------------------------------------------------------
	// 3D element shader
	Shader ourShader("shader.vs", "shader.fs");
	// UI (2D) element shader
	Shader uiShader("UI_shader.vs", "UI_shader.fs");


	// Set up vertex data, vertex buffers, vertex arrays, textures
	// -----------------------------------------------------------------------------
	// Load image with stb_image.h header
	stbi_set_flip_vertically_on_load(true);
	int textureWidth, textureHeight, nrChannels;
	unsigned char* data = stbi_load("textures.png", &textureWidth, &textureHeight, &nrChannels, 0);
	// Generate texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set texture wrapping and filter options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); // free image memory
	
	// Create cube, set up texture coordinates
	Cube cube = Cube(0, 0, 0);
	std::vector<float> colors = {
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
	cube.setTextureCoords(textureWidth, textureHeight, 0, 0, 16, 16);

	// Generate Arrays and Buffers for 3D shader
	unsigned int VBO1, VBO2, VBO3, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO1); //position
	glGenBuffers(1, &VBO2); //color
	glGenBuffers(1, &VBO3); //texCoords
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
	
	// Texture coords attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, cube.texCoords.size() * sizeof(float), &cube.texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	

	// Unbind. Since VBO now unbound, we cannot set up vertex attributes.
	// A VAO and VBO MUST be bound to use glVertexAttribPointer
	// The VAO must be re-bound before drawing, and the shader activated
	// for calls like glDrawArrays to work.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	// Define UI elements
	//Text text(0.0f, 0.0f, 16.0f, 16.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, "FPS");
	TwoDimensionalObject text(0.0f, 0.0f, 16.0f, 16.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, 504.0f, 512.0f, 512.0f);
	
	// Arrays and buffers for UI shader
	unsigned int UI_VAO, UI_VBO1, UI_VBO2, UI_EBO;
	glGenVertexArrays(1, &UI_VAO);
	glGenBuffers(1, &UI_VBO1);
	glGenBuffers(1, &UI_VBO2);
	glGenBuffers(1, &UI_EBO);
	// Bind UI VAO
	glBindVertexArray(UI_VAO);
	// Set up buffer data
	glBindBuffer(GL_ARRAY_BUFFER, UI_VBO1);
	glBufferData(GL_ARRAY_BUFFER, text.vertices.size() * sizeof(float), &text.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UI_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, text.indices.size() * sizeof(unsigned int), &text.indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, UI_VBO2);
	glBufferData(GL_ARRAY_BUFFER, text.texCoords.size() * sizeof(float), &text.texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	
	
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
		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);
		// Draw 3D
		glEnable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		// Draw UI
		uiShader.use();
		glBindVertexArray(UI_VAO);
		//glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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