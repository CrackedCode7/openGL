#include "Block.h"

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


std::vector<float> Block::getFrontFaceVertices()
{
	std::vector<float> vertices = {
		0.0f + x, 0.0f + y, 1.0f + z, // 0
		1.0f + x, 0.0f + y, 1.0f + z, // 3
		1.0f + x, 1.0f + y, 1.0f + z, // 6
		0.0f + x, 0.0f + y, 1.0f + z, // 0
		1.0f + x, 1.0f + y, 1.0f + z, // 6
		0.0f + x, 1.0f + y, 1.0f + z, // 9
	};	

	return vertices;
}


std::vector<float> Block::getFrontFaceTexCoords()
{
	std::vector<float> texCoords = {
		(float)posX, (float)(textureHeight - posY - sizeY),				// 0
		(float)(posX + sizeX), (float)(textureHeight - posY - sizeY), 	// 3
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 6
		(float)posX, (float)(textureHeight - posY - sizeY),				// 0
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 6
		(float)posX, (float)(textureHeight - posY), 					// 9
	};

	return texCoords;
}


std::vector<float> Block::getRightFaceVertices()
{
	std::vector<float> vertices = {
		1.0f + x, 0.0f + y, 1.0f + z, // 4 
		1.0f + x, 0.0f + y, 0.0f + z, // 15
		1.0f + x, 1.0f + y, 0.0f + z, // 18
		1.0f + x, 0.0f + y, 1.0f + z, // 4 
		1.0f + x, 1.0f + y, 0.0f + z, // 18
		1.0f + x, 1.0f + y, 1.0f + z, // 7
	};
	
	return vertices;
}


std::vector<float> Block::getRightFaceTexCoords()
{
	std::vector<float> texCoords = {
		(float)posX, (float)(textureHeight - posY - sizeY), 			// 4
		(float)(posX + sizeX), (float)(textureHeight - posY - sizeY), 	// 15
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 18
		(float)posX, (float)(textureHeight - posY - sizeY), 			// 4
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 18
		(float)posX, (float)(textureHeight - posY), 					// 7
	};
	
	return texCoords;
}


std::vector<float> Block::getTopFaceVertices()
{
	std::vector<float> vertices = {
		0.0f + x, 1.0f + y, 1.0f + z, // 10
		1.0f + x, 1.0f + y, 1.0f + z, // 8
		1.0f + x, 1.0f + y, 0.0f + z, // 19
		0.0f + x, 1.0f + y, 1.0f + z, // 10
		1.0f + x, 1.0f + y, 0.0f + z, // 19
		0.0f + x, 1.0f + y, 0.0f + z, // 21
	};
	
	return vertices;
}


std::vector<float> Block::getTopFaceTexCoords()
{
	std::vector<float> texCoords = {
		(float)(posX + sizeX), (float)(textureHeight - posY - sizeY), 		// 10
		(float)(posX + 2 * sizeX), (float)(textureHeight - posY - sizeY), 	// 8
		(float)(posX + 2 * sizeX), (float)(textureHeight - posY), 			// 19
		(float)(posX + sizeX), (float)(textureHeight - posY - sizeY), 		// 10
		(float)(posX + 2 * sizeX), (float)(textureHeight - posY), 			// 19
		(float)(posX + sizeX), (float)(textureHeight - posY), 				// 21
	};
	
	return texCoords;
}


std::vector<float> Block::getLeftFaceVertices()
{
	std::vector<float> vertices = {
		0.0f + x, 0.0f + y, 0.0f + z, // 12
		0.0f + x, 0.0f + y, 1.0f + z, // 1
		0.0f + x, 1.0f + y, 1.0f + z, // 11
		0.0f + x, 0.0f + y, 0.0f + z, // 12
		0.0f + x, 1.0f + y, 1.0f + z, // 11
		0.0f + x, 1.0f + y, 0.0f + z, // 22
	};
	
	return vertices;
}


std::vector<float> Block::getLeftFaceTexCoords()
{
	std::vector<float> texCoords = {
		(float)posX, (float)(textureHeight - posY - sizeY), 			// 12
		(float)(posX + sizeX), (float)(textureHeight - posY - sizeY), 	// 1
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 11
		(float)posX, (float)(textureHeight - posY - sizeY), 			// 12
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 11
		(float)posX, (float)(textureHeight - posY), 					// 22
	};
	
	return texCoords;
}


std::vector<float> Block::getBackFaceVertices()
{
	std::vector<float> vertices = {
		1.0f + x, 0.0f + y, 0.0f + z, // 16
		0.0f + x, 0.0f + y, 0.0f + z, // 13
		0.0f + x, 1.0f + y, 0.0f + z, // 23
		1.0f + x, 0.0f + y, 0.0f + z, // 16
		0.0f + x, 1.0f + y, 0.0f + z, // 23
		1.0f + x, 1.0f + y, 0.0f + z, // 20
	};
	
	return vertices;
}


std::vector<float> Block::getBackFaceTexCoords()
{
	std::vector<float> texCoords = {
		(float)posX, (float)(textureHeight - posY - sizeY), 			// 16
		(float)(posX + sizeX), (float)(textureHeight - posY - sizeY), 	// 13
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 23
		(float)posX, (float)(textureHeight - posY - sizeY), 			// 16
		(float)(posX + sizeX), (float)(textureHeight - posY), 			// 23
		(float)posX, (float)(textureHeight - posY), 					// 20
	};
	
	return texCoords;
}


std::vector<float> Block::getBottomFaceVertices()
{
	std::vector<float> vertices = {
		0.0f + x, 0.0f + y, 0.0f + z, // 14
		1.0f + x, 0.0f + y, 0.0f + z, // 17
		1.0f + x, 0.0f + y, 1.0f + z, // 5
		0.0f + x, 0.0f + y, 0.0f + z, // 14
		1.0f + x, 0.0f + y, 1.0f + z, // 5
		0.0f + x, 0.0f + y, 1.0f + z, // 2
	};
	
	return vertices;
}


std::vector<float> Block::getBottomFaceTexCoords()
{
	std::vector<float> texCoords = {
		(float)(posX + 2 * sizeX), (float)(textureHeight - posY - sizeY), 	// 14
		(float)(posX + 3 * sizeX), (float)(textureHeight - posY - sizeY), 	// 17
		(float)(posX + 3 * sizeX), (float)(textureHeight - posY), 		// 5
		(float)(posX + 2 * sizeX), (float)(textureHeight - posY - sizeY), 	// 14
		(float)(posX + 3 * sizeX), (float)(textureHeight - posY), 		// 5
		(float)(posX + 2 * sizeX), (float)(textureHeight - posY), 		// 2
	};
	
	return texCoords;
}


Block::Block(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Block::Block() {};