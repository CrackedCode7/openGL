#include "Chunk.h"

#include "Cube.h"


Chunk::Chunk(int x, int z)
{
    this -> x = x;
    this -> z = z;

    // Generate blocks
    int index = 0;
    for (int i=0; i<16; i++)
    {
        for (int j=0; j<16; j++)
        {
            for (int k=0; k<16; k++)
            {
                blockData.push_back(Cube(i+16*x, j, k+16*z));
                blockData[index].setTextureCoords(512, 512, 0, 0, 16, 16); // Change this when block class implemented
                index++;
            }
        }
    }

    // Construct mesh on generation
    for (int i=0; i<blockData.size(); i++)
	{
		for (int j=0; j<72; j++)
		{
			vertices.push_back(blockData[i].vertices[j]);
		}
		for (int j=0; j<48; j++)
		{
			texCoords.push_back(blockData[i].texCoords[j]);
		}
		for (int j=0; j<36; j++)
		{
			indices.push_back(blockData[i].indices[j]+24*i);
		}
	}
}