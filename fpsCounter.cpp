#include "fpsCounter.h"


fpsCounter::fpsCounter(float xPos, float yPos, float xSize, float ySize)
{
    vertices = {
        xPos, yPos-ySize, 0.0f, // bottom left
		xPos+xSize, yPos-ySize, 0.0f, // bottom right
		xPos+xSize, yPos, 0.0f, // top right
		xPos, yPos, 0.0f // top left
    };

    indices = {
        0, 1, 2,
		0, 2, 3
    };
}


void fpsCounter::setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY)
{
    texCoords = {
        (float)posX/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight,
        (float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY-sizeY)/textureHeight,
        (float)(posX+sizeX)/textureWidth, (float)(textureHeight-posY)/textureHeight,
        (float)posX/textureWidth, (float)(textureHeight-posY)/textureHeight
    };
}