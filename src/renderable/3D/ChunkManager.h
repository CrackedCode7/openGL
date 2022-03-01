#pragma once

#include "Chunk.h"

#include <vector>


class ChunkManager
{
	public:
	
		int renderDistance = 12;
		
		std::vector<Chunk> chunks;
		void updateChunksToRender(int playerChunkX, int playerChunkZ);
		
		ChunkManager(int renderDistance);
		ChunkManager();
};