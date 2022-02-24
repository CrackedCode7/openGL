#include "Block.h"

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Block::Block(){};


Block::Block(float x, float y, float z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;

    vertices = {
        0.0f+x, 0.0f+y, 1.0f+z, // 0
		0.0f+x, 0.0f+y, 1.0f+z, // 1
		0.0f+x, 0.0f+y, 1.0f+z, // 2
        1.0f+x, 0.0f+y, 1.0f+z, // 3
		1.0f+x, 0.0f+y, 1.0f+z, // 4 
		1.0f+x, 0.0f+y, 1.0f+z, // 5
        1.0f+x, 1.0f+y, 1.0f+z, // 6
		1.0f+x, 1.0f+y, 1.0f+z, // 7
		1.0f+x, 1.0f+y, 1.0f+z, // 8
        0.0f+x, 1.0f+y, 1.0f+z, // 9
		0.0f+x, 1.0f+y, 1.0f+z, // 10
		0.0f+x, 1.0f+y, 1.0f+z, // 11
        0.0f+x, 0.0f+y, 0.0f+z, // 12
		0.0f+x, 0.0f+y, 0.0f+z, // 13
		0.0f+x, 0.0f+y, 0.0f+z, // 14
        1.0f+x, 0.0f+y, 0.0f+z, // 15
		1.0f+x, 0.0f+y, 0.0f+z, // 16
		1.0f+x, 0.0f+y, 0.0f+z, // 17
        1.0f+x, 1.0f+y, 0.0f+z, // 18
		1.0f+x, 1.0f+y, 0.0f+z, // 19
		1.0f+x, 1.0f+y, 0.0f+z, // 20
        0.0f+x, 1.0f+y, 0.0f+z, // 21
		0.0f+x, 1.0f+y, 0.0f+z, // 22
		0.0f+x, 1.0f+y, 0.0f+z  // 23
        };

    indices = {
        0, 3, 6, // front
        0, 6, 9, // front
        4, 15, 18, // right
        4, 18, 7, // right
        10, 8, 19, // top
        10, 19, 21, // top
        12, 1, 11, // left
        12, 11, 22, // left
        16, 13, 23, // back
        16, 23, 20, // back
        14, 17, 5, // bottom
        14, 5, 2 // bottom
    };
	
	colors = {
		1.0f, 0.0f, 0.0f, // 0
		1.0f, 0.0f, 0.0f, // 1
		1.0f, 0.0f, 0.0f, // 2
		1.0f, 0.0f, 0.0f, // 3
		1.0f, 0.0f, 0.0f, // 4
		1.0f, 0.0f, 0.0f, // 5
		1.0f, 0.0f, 0.0f, // 6
		1.0f, 0.0f, 0.0f, // 7
		1.0f, 0.0f, 0.0f, // 8
		1.0f, 0.0f, 0.0f, // 9
		1.0f, 0.0f, 0.0f, // 10
		1.0f, 0.0f, 0.0f, // 11
		1.0f, 0.0f, 0.0f, // 12
		1.0f, 0.0f, 0.0f, // 13
		1.0f, 0.0f, 0.0f, // 14
		1.0f, 0.0f, 0.0f, // 15
		1.0f, 0.0f, 0.0f, // 16
		1.0f, 0.0f, 0.0f, // 17
		1.0f, 0.0f, 0.0f, // 18
		1.0f, 0.0f, 0.0f, // 19
		1.0f, 0.0f, 0.0f, // 20
		1.0f, 0.0f, 0.0f, // 21
		1.0f, 0.0f, 0.0f, // 22
		1.0f, 0.0f, 0.0f  // 23
	};
}


void Block::setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY)
{
	this -> textureWidth = textureWidth;
	this -> textureHeight = textureHeight;

	// Sides utilize the first texture from atlas at posX, posY then top then bottom offset by sizes 
	texCoords = {
		(float)posX, (float)(textureHeight-posY-sizeY),				// 0
		(float)(posX+sizeX), (float)(textureHeight-posY-sizeY), 	// 1
		(float)(posX+2*sizeX), (float)(textureHeight-posY), 		// 2
		(float)(posX+sizeX), (float)(textureHeight-posY-sizeY), 	// 3
		(float)posX, (float)(textureHeight-posY-sizeY), 			// 4
		(float)(posX+3*sizeX), (float)(textureHeight-posY), 		// 5
		(float)(posX+sizeX), (float)(textureHeight-posY), 			// 6
		(float)posX, (float)(textureHeight-posY), 					// 7
		(float)(posX+2*sizeX), (float)(textureHeight-posY-sizeY), 	// 8
		(float)posX, (float)(textureHeight-posY), 					// 9
		(float)(posX+sizeX), (float)(textureHeight-posY-sizeY), 	// 10
		(float)(posX+sizeX), (float)(textureHeight-posY), 			// 11
		(float)posX, (float)(textureHeight-posY-sizeY), 			// 12
		(float)(posX+sizeX), (float)(textureHeight-posY-sizeY), 	// 13
		(float)(posX+2*sizeX), (float)(textureHeight-posY-sizeY), 	// 14
		(float)(posX+sizeX), (float)(textureHeight-posY-sizeY), 	// 15
		(float)posX, (float)(textureHeight-posY-sizeY), 			// 16
		(float)(posX+3*sizeX), (float)(textureHeight-posY-sizeY), 	// 17
		(float)(posX+sizeX), (float)(textureHeight-posY), 			// 18
		(float)(posX+2*sizeX), (float)(textureHeight-posY), 		// 19
		(float)posX, (float)(textureHeight-posY), 					// 20
		(float)(posX+sizeX), (float)(textureHeight-posY), 			// 21
		(float)posX, (float)(textureHeight-posY), 					// 22
		(float)(posX+sizeX), (float)(textureHeight-posY), 			// 23
	};
}