#pragma once

#include <vector>


class fpsCounter
{
    public:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;

        fpsCounter(float xPos, float yPos, float xSize, float ySize);
        void setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY);
};