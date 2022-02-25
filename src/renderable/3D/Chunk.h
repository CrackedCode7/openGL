#pragma once

#include "Block.h"

#include <map>
#include <vector>


class Chunk
{
    public:
		// General attributes
        int x = 0;
        int z = 0;
		int xSize = 16;
		int ySize = 32;
		int zSize = 16;
		bool loaded = false;
		std::vector<Block> blockData;
		
		// OpenGL attributes/buffers
		unsigned int VAO = 0;
		unsigned int vertexVBO = 0;
		unsigned int textureVBO = 0;
		
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