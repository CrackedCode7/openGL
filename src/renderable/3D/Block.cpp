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
        0.0f+x, 0.0f+y, 1.0f+z,
		0.0f+x, 0.0f+y, 1.0f+z,
		0.0f+x, 0.0f+y, 1.0f+z,
        1.0f+x, 0.0f+y, 1.0f+z,
		1.0f+x, 0.0f+y, 1.0f+z,
		1.0f+x, 0.0f+y, 1.0f+z,
        1.0f+x, 1.0f+y, 1.0f+z,
		1.0f+x, 1.0f+y, 1.0f+z,
		1.0f+x, 1.0f+y, 1.0f+z,
        0.0f+x, 1.0f+y, 1.0f+z,
		0.0f+x, 1.0f+y, 1.0f+z,
		0.0f+x, 1.0f+y, 1.0f+z,
        0.0f+x, 0.0f+y, 0.0f+z,
		0.0f+x, 0.0f+y, 0.0f+z,
		0.0f+x, 0.0f+y, 0.0f+z,
        1.0f+x, 0.0f+y, 0.0f+z,
		1.0f+x, 0.0f+y, 0.0f+z,
		1.0f+x, 0.0f+y, 0.0f+z,
        1.0f+x, 1.0f+y, 0.0f+z,
		1.0f+x, 1.0f+y, 0.0f+z,
		1.0f+x, 1.0f+y, 0.0f+z,		
        0.0f+x, 1.0f+y, 0.0f+z,
		0.0f+x, 1.0f+y, 0.0f+z,
		0.0f+x, 1.0f+y, 0.0f+z
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
};


void Block::setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY)
{
	this -> textureWidth = textureWidth;
	this -> textureHeight = textureHeight;

	// Sides utilize the first texture from atlas at posX, posY then top then bottom offset by sizes 
	texCoords = {
		(float)posX/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 0
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 1
		(float)(posX+2*sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 2
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 3
		(float)posX/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 4
		(float)(posX+3*sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 5
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 6
		(float)posX/textureWidth, (float)(textureHeight-posY)/textureHeight, // 7
		(float)(posX+2*sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 8
		(float)posX/textureWidth, (float)(textureHeight-posY)/textureHeight, // 9
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 10
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 11
		(float)posX/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 12
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 13
		(float)(posX+2*sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 14
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 15
		(float)posX/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 16
		(float)(posX+3*sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight, // 17
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 18
		(float)(posX+2*sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 19
		(float)posX/textureWidth, (float)(textureHeight-posY)/textureHeight, // 20
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 21
		(float)posX/textureWidth, (float)(textureHeight-posY)/textureHeight, // 22
		(float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight, // 23
	};
}