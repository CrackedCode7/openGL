#pragma once

#include "Block.h"

#include <map>
#include <vector>


class Chunk
{
    public:
		// General attributes
        int x;
        int z;
		bool loaded = false;
		std::map<std::vector<int>, Block> blockData;
        //std::vector<Block> blockData;
		
		// OpenGL attributes/buffers
		unsigned int VAO;
		unsigned int vertexVBO;
		unsigned int textureVBO;
		unsigned int EBO;
		
		// Buffer data storage attributes
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;
		
		// Functions for loading/unloading (buffer creation/deletion)
		void load();
		void unload();
		
		// Meshing function
		void mesh();
		
		// Drawing function
		void draw();
		
		// Constructor
        Chunk(int x, int y);
};