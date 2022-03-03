#include "ChunkManager.h"

#include "Chunk.h"
#include <vector>
#include <cmath>
#include <algorithm>


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
					chunks.push_back(Chunk(i, j));
				}
			}
		}
	}
	
	// Remove previously loaded chunks outside of render distance
	std::vector<int> indicesToRemove;
	for (int i=0; i<chunks.size(); i++)
	{
		double chunkDistance = sqrt( pow(chunks[i].x - playerChunkX, 2) + pow(chunks[i].z - playerChunkZ, 2) );
		if (chunkDistance > renderDistance)
		{
			chunks[i].unload();
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