#include "ChunkManager.h"

#include "Chunk.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <thread>


ChunkManager::ChunkManager() {}


ChunkManager::ChunkManager(int renderDistance)
{
	this->renderDistance = renderDistance;
}


void ChunkManager::updateChunksToRender(int playerChunkX, int playerChunkZ)
{
	// Add chunks that need to be loaded/rendered
	for (int i = playerChunkX - renderDistance; i <= playerChunkX + renderDistance; i++)
	{
		for (int j = playerChunkZ - renderDistance; j <= playerChunkZ + renderDistance; j++)
		{
			// Inside render distance AND not already existing
			double chunkDistance = sqrt( pow(i - playerChunkX, 2) + pow(j-playerChunkZ, 2) );
			if (chunkDistance <= renderDistance)
			{
				bool isChunkLoaded = false;
				for (int k=0; k < chunks.size(); k++)
				{
					if ( (i == chunks[k].x) && (j == chunks[k].z) )
					{
						isChunkLoaded = true;
					}
				}
				// Add chunk if not loaded already
				if (!isChunkLoaded)
				{
					std::thread t(&ChunkManager::generateChunk, this, i, j);
					t.detach();
				}
			}
		}
	}
	
	// Load (create gpu portion) of chunks that have been generated
	mtx.lock();
	for (int i = 0; i < chunksToBeLoaded.size(); i++)
	{
		chunksToBeLoaded[i].loadGPU();
		chunks.push_back(chunksToBeLoaded[i]);
	}
	chunksToBeLoaded.clear();
	mtx.unlock();
	
	// Remove previously loaded chunks outside of render distance
	std::vector<int> indicesToRemove;
	for (int i=0; i<chunks.size(); i++)
	{
		double chunkDistance = sqrt( pow(chunks[i].x - playerChunkX, 2) + pow(chunks[i].z - playerChunkZ, 2) );
		if (chunkDistance > renderDistance)
		{
			chunks[i].unloadGPU();
			indicesToRemove.push_back(i);
		}
	}
	
	// Sort indices greatest to largest to remove all at once
	std::sort(indicesToRemove.begin(), indicesToRemove.end(), std::greater<int>());
	
	// Erase chunks
	for (int i=0; i<indicesToRemove.size(); i++)
	{
		chunks.erase(chunks.begin() + indicesToRemove[i]);
	}
}


void ChunkManager::generateChunk(int x, int z)
{
	// Create chunk on cpu and add to chunk list
	Chunk chunk = Chunk(x, z);

	mtx.lock();
	chunksToBeLoaded.push_back(chunk);
	mtx.unlock();
}