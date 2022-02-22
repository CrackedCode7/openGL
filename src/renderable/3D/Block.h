#pragma once

#include <vector>


class Block
{
    public:

        float x;
        float y;
        float z;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
		std::vector<float> colors;
		std::vector<float> texCoords;
        int textureWidth;
        int textureHeight;

        Block(float x, float y, float z);
        void setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY);
};