#pragma once

#include "text.h"
#include <vector>


class DebugScreen
{
    public:
		
		// OpenGL buffers
		unsigned int VAO;
		unsigned int textureVBO;
		unsigned int vertexVBO;
		unsigned int EBO;
		
		// Buffer data storage
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;

		// Functions to update contents
		void updateText(Text* fpsText, Text* tpsText);
		
		// Draw function
		void draw();
		
        DebugScreen();
};