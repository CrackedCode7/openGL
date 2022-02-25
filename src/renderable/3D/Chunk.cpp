#include "Chunk.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> // glfwGetTime()
#include <map>
#include <vector>
#include "Block.h"
#include "src/util/util.h"

#include <iostream>


void Chunk::load()
{
	// Update chunk state
	loaded = true;

	// Set up OpenGL buffers
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &textureVBO);
	//glGenBuffers(1, &EBO);
	
	// VAO bound before setting up buffer data
	glBindVertexArray(VAO);
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 vertices.size() * sizeof(float), 
				 &vertices[0], 
				 GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 texCoords.size() * sizeof(float), 
				 &texCoords[0], 
				 GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Chunk::unload()
{
	// Update chunk state
	loaded = false;
	
	// Clear VAO for reuse
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GLint maxAttrib;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttrib);
	for (int attribIx = 0; attribIx < maxAttrib; ++attribIx)
	{
		glDisableVertexAttribArray(attribIx);
		glVertexAttribPointer(attribIx, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glVertexAttribDivisor(attribIx, 0);
	}
	
	// Delete buffers. The VAO, VBOs can be reused when reloading
	// Their values are set to 0, which means it is not a buffer object.
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &textureVBO);
}


void Chunk::draw()
{
	// Make sure chunk loaded
	if (loaded)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
}


bool Chunk::findBlock(int x, int y, int z)
{
	std::cout << x << " " << y << " " << z << std::endl;
	if ( (x >= 0 && x < xSize) && (y >= 0 && y < ySize) && (z >= 0 && z < zSize) )
	{
		int index = x + xSize * z + xSize * zSize * y;
		if (!blockData[index].transparent)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


void Chunk::mesh()
{
    for (int i=0; i<blockData.size(); i++)
	{
		// key is first, block is second

		// Check faces and add appropriate indices
		int x = positiveModulo(blockData[i].x, xSize);
		int y = blockData[i].y;
		int z = positiveModulo(blockData[i].z, zSize);
		// Front face
		if (!findBlock(x, y, z+1))
		{
			std::vector<float> faceVerts = blockData[i].getFrontFaceVertices();
			vertices.insert(vertices.end(), faceVerts.begin(), faceVerts.end());
			
			std::vector<float> faceTexCoords = blockData[i].getFrontFaceTexCoords();
			texCoords.insert(texCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
		}
		// Right face
		if (!findBlock(x+1, y, z))
		{
			std::vector<float> faceVerts = blockData[i].getRightFaceVertices();
			vertices.insert(vertices.end(), faceVerts.begin(), faceVerts.end());
			
			std::vector<float> faceTexCoords = blockData[i].getRightFaceTexCoords();
			texCoords.insert(texCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
		}
		// Top face
		if (!findBlock(x, y+1, z))
		{
			std::vector<float> faceVerts = blockData[i].getTopFaceVertices();
			vertices.insert(vertices.end(), faceVerts.begin(), faceVerts.end());
			
			std::vector<float> faceTexCoords = blockData[i].getTopFaceTexCoords();
			texCoords.insert(texCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
		}
		// Left face
		if (!findBlock(x-1, y, z))
		{
			std::vector<float> faceVerts = blockData[i].getLeftFaceVertices();
			vertices.insert(vertices.end(), faceVerts.begin(), faceVerts.end());
			
			std::vector<float> faceTexCoords = blockData[i].getLeftFaceTexCoords();
			texCoords.insert(texCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
		}
		// Back face
		if (!findBlock(x, y, z-1))
		{
			std::vector<float> faceVerts = blockData[i].getBackFaceVertices();
			vertices.insert(vertices.end(), faceVerts.begin(), faceVerts.end());
			
			std::vector<float> faceTexCoords = blockData[i].getBackFaceTexCoords();
			texCoords.insert(texCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
		}
		// Bottom face
		if (!findBlock(x, y-1, z))
		{
			std::vector<float> faceVerts = blockData[i].getBottomFaceVertices();
			vertices.insert(vertices.end(), faceVerts.begin(), faceVerts.end());
			
			std::vector<float> faceTexCoords = blockData[i].getBottomFaceTexCoords();
			texCoords.insert(texCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
		}
	}
}


Chunk::Chunk(){};


Chunk::Chunk(int x, int z)
{
    this -> x = x;
    this -> z = z;
	
	double startTime = glfwGetTime();
    // Generate blocks
    int index = 0;
    for (int i=0; i<16; i++)
    {
        for (int k=0; k<16; k++)
        {
            for (int j=0; j<16; j++)
            {
                blockData.push_back(Block(i+16*x, j, k+16*z));
                index++;
            }
        }
    }
	double genTime = glfwGetTime();

    // Construct mesh on generation
	// Pre-allocate memory for testing
	//vertices.reserve(16*16*16*24*3);
	//texCoords.reserve(16 * 16 * 16 * 24*3);
	mesh();
	double meshTime = glfwGetTime();
	
	// Create VAO on chunk creation
	glGenVertexArrays(1, &VAO);
	
	// Load data into buffers for rendering
	// Assumes that when a chunk is generated it should be ready to render
	load();
	double loadTime = glfwGetTime();
	
	std::cout << "Generating chunk took " << genTime-startTime << std::endl;
	std::cout << "Generating mesh took " << meshTime-genTime << std::endl;
	std::cout << "Loading chunk took " << loadTime-meshTime << std::endl;
}