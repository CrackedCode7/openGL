#include <glad/glad.h> // before glfw (I think it HAS to be)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <map>
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
	std::map<std::vector<int>, Chunk> chunks;
	std::vector<Chunk*> loadedChunks;
	for (int i=-5; i<=5; i++)
	{
		for (int j=-5; j<=5; j++)
		{
			chunks[std::vector<int>{i, j}] = Chunk (i, j);
			loadedChunks.push_back(&chunks[std::vector<int>{i, j}]);
		}
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
				
				for (int i=0; i<loadedChunks.size(); i++)
				{
					if (sqrt(pow((loadedChunks[i]->x-lastPlayerChunkX), 2) + pow((loadedChunks[i]->z-lastPlayerChunkZ), 2)) >= 5)
					{
						loadedChunks[i] -> unload();
					}
					else if (!loadedChunks[i] -> loaded)
					{
						loadedChunks[i] -> load();
					}
				}
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
		// Setup uniforms in fragment shader
		ourShader.setVec2("textureSize", glm::vec2((float)texture.width, (float)texture.height));
		// Bind Texture (texture uniform, frag shader)
		glBindTexture(GL_TEXTURE_2D, texture.texture);
		// Draw 3D
		for (int i = 0; i<loadedChunks.size(); i++)
		{
			loadedChunks[i] -> draw();
		}
		
		// Draw UI
		uiShader.use();
		debugScreen.draw();


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	

	// Terminate glfw before the program ends
	// -----------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}