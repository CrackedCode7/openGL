#include <glad/glad.h> // before glfw (I think it HAS to be)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <cmath> // floor
#include <string>

#include "src/shaders/Shader.h"
#include "src/camera/Camera.h"
#include "src/renderable/2D/text.h"
#include "src/textures/Texture.h"
#include "src/renderable/3D/Chunk.h"
#include "src/UI/debugScreen.h"
#include "src/setup/GLFW/windowSetup.h"


int main()
{
	// Initialize GLFW and versions
	if (!window::initializeGLFW())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	
	// Create GLFW window for rendering
	GLFWwindow* window = window::createWindow();
	

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
	Shader ourShader("src/shaders/3D/shader.vs", "src/shaders/3D/shader.fs");
	// UI (2D) element shader
	Shader uiShader("src/shaders/UI/UI_shader.vs", "src/shaders/UI/UI_shader.fs");


	// Set up vertex data, vertex buffers, vertex arrays, textures
	// -----------------------------------------------------------------------------
	// Load texture atlas
	Texture texture("src/textures/textures.png");


	// Create chunks
	std::vector<Chunk> chunks;
	for (int i=0; i<5; i++)
	{
		chunks.push_back(Chunk (i, 0));
	}
	
	// Define UI elements
	// FPS counter initializes to "XXXX", updated in tick/frame loop later.
	Text fpsText("FPS:XXXX", 0.0f, 0.0f, 10.0f, 10.0f, (float)window::SCR_WIDTH, (float)window::SCR_HEIGHT, &texture);
	Text tpsText("TPS:XX", 0.0f, 10.0f, 10.0f, 10.0f, (float)window::SCR_WIDTH, (float)window::SCR_HEIGHT, &texture);
	DebugScreen debugScreen;
	debugScreen.updateText(&fpsText, &tpsText);
	
	
	// Set up initial camera position, look at, and up vectors
	// Set up perspective projection, view, and model matrices
	// -----------------------------------------------------------------------------
	Camera camera(0.0f, 20.0f, -5.0f, window::SCR_WIDTH, window::SCR_HEIGHT);
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
			std::string fpsStr = "FPS:" + std::to_string(frameCount);
			fpsText.updateText(fpsStr);
			std::string tpsStr = "TPS:" + std::to_string(tickCount);
			tpsText.updateText(tpsStr);
			
			debugScreen.updateText(&fpsText, &tpsText);
			
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
			window::processInput(window);


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
		debugScreen.draw();


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
	//glDeleteVertexArrays(1, &UI_VAO);
	//glDeleteBuffers(1, &UI_VBO1);
	//glDeleteBuffers(1, &UI_VBO2);
	//glDeleteBuffers(1, &UI_EBO);
	

	// Terminate glfw before the program ends
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}