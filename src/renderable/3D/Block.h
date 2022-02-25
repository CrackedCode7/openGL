#pragma once

#include <vector>


class Block
{
    public:
		// Block position
        float x;
        float y;
        float z;
		
		// Texture attributes
		int posX = 0;
		int posY = 0;
		int sizeX = 16;
		int sizeY = 16;
        int textureWidth = 512;
        int textureHeight = 512;
		
		// Meshing functions to be called by chunk
        std::vector<float> getFrontFaceVertices();
        std::vector<float> getFrontFaceTexCoords();
		std::vector<float> getRightFaceVertices();
		std::vector<float> getRightFaceTexCoords();
		std::vector<float> getTopFaceVertices();
		std::vector<float> getTopFaceTexCoords();
		std::vector<float> getLeftFaceVertices();
		std::vector<float> getLeftFaceTexCoords();
		std::vector<float> getBackFaceVertices();
		std::vector<float> getBackFaceTexCoords();
		std::vector<float> getBottomFaceVertices();
		std::vector<float> getBottomFaceTexCoords();
		
		// Constructors
		Block();
        Block(float x, float y, float z);
};