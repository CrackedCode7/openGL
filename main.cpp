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
#include <string>

#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "text.h"
#include "twoDimensionalObject.h"
#include "Texture.h"
#include "Chunk.h"

#include "stb_image.h"


// Constant settings
// ---------------------------------------------------------------------------------
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;


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
	Texture texture("textures.png");

	// Create chunks
	std::vector<Chunk> chunks;
	for (int i=0; i<5; i++)
	{
		chunks.push_back(Chunk (i, 0));
	}
	
	// Define UI elements
	// FPS counter initializes to "XXXX", updated in tick/frame loop later.
	Text text("FPS:XXXX", 0.0f, 0.0f, 12.0f, 12.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, texture);
	
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
	glBufferData(GL_ARRAY_BUFFER, text.vertices.size() * sizeof(float), &text.vertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UI_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, text.indices.size() * sizeof(unsigned int), &text.indices[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, UI_VBO2);
	glBufferData(GL_ARRAY_BUFFER, text.texCoords.size() * sizeof(float), &text.texCoords[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	
	
	// Set up initial camera position, look at, and up vectors
	// Set up perspective projection, view, and model matrices
	// -----------------------------------------------------------------------------
	Camera camera(0.0f, 20.0f, -5.0f, SCR_WIDTH, SCR_HEIGHT);
	int lastPlayerChunkX = floor(camera.cameraPos[0]);
	int playerChunkX = floor(camera.cameraPos[0]);
	int lastPlayerChunkZ = floor(camera.cameraPos[1]);
	int playerChunkZ = floor(camera.cameraPos[1]);


	// OpenGL setup functions
	// -----------------------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	

	// Render loop
	// -----------------------------------------------------------------------------
	// Framerate variables
	double startTime = glfwGetTime();
	double previousTime = glfwGetTime();
	double previousTickTime = glfwGetTime();
	double previousFrameTime = glfwGetTime();
	double tickTime = 1.0/60.0;
	int frameCount = 0;
	int tickCount = 0;

	// Main loop
	while (!glfwWindowShouldClose(window))
    {
		// Framerate counting/displaying
		// -------------------------------------------------------------------------
		double currentTime = glfwGetTime();
		
		frameCount++;
		
		// Output frames and ticks once per second
		if (currentTime - previousTime >= 1.0)
		{
			// Edit framerate text
			std::string fpsText = "FPS:" + std::to_string(frameCount);
			text.updateText(fpsText);
			// Update buffers
			glBindVertexArray(UI_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, UI_VBO1);
			glBufferSubData(GL_ARRAY_BUFFER, 0, text.vertices.size() * sizeof(float), &text.vertices[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UI_EBO);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, text.indices.size() * sizeof(unsigned int), &text.indices[0]);
			glBindBuffer(GL_ARRAY_BUFFER, UI_VBO2);
			glBufferSubData(GL_ARRAY_BUFFER, 0, text.texCoords.size() * sizeof(float), &text.texCoords[0]);
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			
			std::cout << tickCount << " ticks " << frameCount << " fps" << std::endl;
			
			frameCount = 0;
			tickCount = 0;

			previousTime = currentTime;
		}
		
		// Ticking system
		// -------------------------------------------------------------------------
		// Try to tick 60 times per second
		
		if (floor((currentTime-startTime)/tickTime) != floor((previousTickTime-startTime)/tickTime))
		{
			// input
			// ---------------------------------------------------------------------
			processInput(window, camera);


			// Camera input handling
			// ---------------------------------------------------------------------
			camera.handleInput(window);


			// Chunk removal
			// ---------------------------------------------------------------------
			playerChunkX = floor(camera.cameraPos[0] / 16);
			playerChunkZ = floor(camera.cameraPos[2] / 16);
			
			if ((playerChunkX != lastPlayerChunkX) || (playerChunkZ != lastPlayerChunkZ))
			{	
				// Update last chunk to match current player chunk
				lastPlayerChunkX = playerChunkX;
				lastPlayerChunkZ = playerChunkZ;
				/*
				double meshTimeStart = glfwGetTime();
				// Clear mesh
				vertices.clear();
				indices.clear();
				texCoords.clear();
				chunks.clear();
				for (int i=0; i<5; i++)
				{
					float distance = sqrt(pow(playerChunkX-i, 2) + pow(playerChunkZ-0, 2));
					if (distance < 10.0f)
					{
						chunks.push_back(Chunk (i, 0));
					}
				}
				// Combine chunk verts, indices, and texCoords
				int currentIndex = 0;
				for (int i=0; i<chunks.size(); i++)
				{
					for (int j=0; j<chunks[i].vertices.size(); j++)
					{
						vertices.push_back(chunks[i].vertices[j]);
					}
					for (int j=0; j<chunks[i].texCoords.size(); j++)
					{
						texCoords.push_back(chunks[i].texCoords[j]);
					}
					for (int j=0; j<chunks[i].indices.size(); j++)
					{
						indices.push_back(chunks[i].indices[j]+currentIndex);
					}
					currentIndex += chunks[i].blockData.size()*24;
				}
				double meshTimeEnd = glfwGetTime();
				double dataManipStart = meshTimeEnd;
				// Send data to buffers
				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO1);
				glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices[0]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), &indices[0]);
				glBindBuffer(GL_ARRAY_BUFFER, VBO3);
				glBufferSubData(GL_ARRAY_BUFFER, 0, texCoords.size() * sizeof(float), &texCoords[0]);
				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				double dataManipEnd = glfwGetTime();
				
				std::cout << "Mesh time: " << meshTimeEnd-meshTimeStart << std::endl;
				std::cout << "Data manipulation time: " << dataManipEnd-dataManipStart << std::endl;*/
			}


			// Tick
			tickCount++;
			previousTickTime = currentTime;
		}
		

		// render
		// -------------------------------------------------------------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Fill mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		// Activate 3D shader
		ourShader.use();
		// Setup uniforms in vertex shader
		ourShader.setMat4("model", camera.model);
		ourShader.setMat4("view", camera.view);
		ourShader.setMat4("projection", camera.projection);
		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, texture.texture);
		// Draw 3D
		for (int i = 0; i<chunks.size(); i++)
		{
			chunks[i].draw();
		}
		
		// Draw UI
		uiShader.use();
		glBindVertexArray(UI_VAO);
		glDrawElements(GL_TRIANGLES, 6*text.objects.size(), GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


	// Optionally de-allocate resources
	// -----------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO1);
	//glDeleteBuffers(1, &VBO2);
	//glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &UI_VAO);
	glDeleteBuffers(1, &UI_VBO1);
	glDeleteBuffers(1, &UI_VBO2);
	glDeleteBuffers(1, &UI_EBO);
	

	// Terminate glfw before the program ends
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}