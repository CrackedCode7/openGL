#pragma once

#include <vector>


class Block
{
    public:

        float x;
        float y;
        float z;
        static std::vector<float> vertices;
        static std::vector<unsigned int> indices;
		static std::vector<float> texCoords;
        int textureWidth;
        int textureHeight;

        void setTextureCoords(int textureWidth, int textureHeight, int posX, int posY, int sizeX, int sizeY);
		
        std::vector<float> getFrontFaceVertices();
        std::vector<float> getFrontFaceIndices();

        std::vector<float> meshRightFace();
        std::vector<float> meshTopFace();
        std::vector<float> meshLeftFace();
        std::vector<float> meshBackFace();
        std::vector<float> meshBottomFace();

		Block();
        Block(float x, float y, float z);
        
};