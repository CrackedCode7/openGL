#pragma once

#include "Chunk.h"

#include <vector>
#include <mutex>


class ChunkManager
{
	public:
	
		int renderDistance = 12;
		
		std::vector<Chunk> chunks;
		std::vector<Chunk> chunksToBeLoaded;
		std::mutex mtx;
		void updateChunksToRender(int playerChunkX, int playerChunkZ);
		void generateChunk(int x, int z);
		
		ChunkManager(int renderDistance);
		ChunkManager();
};