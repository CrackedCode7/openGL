#include "Chunk.h"

#include <glad/glad.h>
#include <map>
#include <vector>
#include "Block.h"


void Chunk::load()
{
	// Depends on data being there already (vertices, etc.)
	// Set up OpenGL buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);
	
	// VAO bound before setting up buffer data
	glBindVertexArray(VAO);
	// Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
				 indices.size() * sizeof(unsigned int), 
				 &indices[0], 
				 GL_DYNAMIC_DRAW);
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 vertices.size() * sizeof(float), 
				 &vertices[0], 
				 GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 texCoords.size() * sizeof(float), 
				 &texCoords[0], 
				 GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	
	// Unbind (don't need EBO because it is per VAO, not global state)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	// Update chunk state
	loaded = true;
}


void Chunk::unload()
{
	// Delete arrays/buffers. The VAO, VBOs, and EBO can be reused when reloading
	// Their values are set to 0, which means it is not a buffer object.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &textureVBO);
	glDeleteBuffers(1, &EBO);
	
	// Update chunk state
	loaded = false;
}


void Chunk::draw()
{
	// Make sure chunk loaded
	if (loaded)
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}


void Chunk::mesh()
{
	
}


Chunk::Chunk(int x, int z)
{
    this -> x = x;
    this -> z = z;
	
	
    // Generate blocks
    int index = 0;
    for (int i=0; i<16; i++)
    {
        for (int k=0; k<16; k++)
        {
            for (int j=0; j<16; j++)
            {
                blockData[std::vector<int>{i+16*x, j, k+16*z}] = Block(i+16*x, j, k+16*z);
                blockData[std::vector<int>{i+16*x, j, k+16*z}].setTextureCoords(512, 512, 0, 0, 16, 16); // Change this when block class implemented
                index++;
            }
        }
    }

    // Construct mesh on generation
	std::map<std::vector<int>, Block>::iterator it;
	int i=0;
    for (it=blockData.begin(); it!=blockData.end(); it++)
	{
		// key is first, block is second
		for (int j=0; j<it->second.vertices.size(); j++)
		{
			vertices.push_back(it->second.vertices[j]);
		}
		for (int j=0; j<it->second.texCoords.size(); j++)
		{
			texCoords.push_back(it->second.texCoords[j]);
		}
		for (int j=0; j<it->second.indices.size(); j++)
		{
			// 24 unique indices per block
			indices.push_back(it->second.indices[j]+24*i);
		}
		i++; // number of blocks
	}
	
	// Load data into buffers for rendering
	// Assumes that when a chunk is generated it should be ready to render
	load();
}