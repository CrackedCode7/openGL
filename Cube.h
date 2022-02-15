#pragma once

#include <vector>


class Cube
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

        Cube(float x, float y, float z);
        void setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY);
};