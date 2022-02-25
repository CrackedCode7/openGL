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
		int xSize = 16;
		int ySize = 16;
		int zSize = 16;
		bool loaded = false;
		std::vector<Block> blockData;
		
		// OpenGL attributes/buffers
		unsigned int VAO;
		unsigned int vertexVBO;
		unsigned int textureVBO;
		
		// Buffer data storage attributes
        std::vector<float> vertices;
        std::vector<float> texCoords;
		
		// Functions for loading/unloading (buffer creation/deletion)
		void load();
		void unload();
		
		// Meshing function
		void mesh();
		bool findBlock(int x, int y, int z);
		
		// Drawing function
		void draw();
		
		// Constructor
		Chunk();
        Chunk(int x, int y);
};