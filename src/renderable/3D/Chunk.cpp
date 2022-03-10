#include "Chunk.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> // glfwGetTime()
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <iterator>
#include "Block.h"
#include "src/util/util.h"

#include <iostream>


void Chunk::generate()
{
	// Generate chunk data if file not found for chunk
	// Generate blocks
	int index = 0;
	for (int j = 0; j < ySize; j++)
	{
		for (int k = 0; k < zSize; k++)
		{
			for (int i = 0; i < xSize; i++)
			{
				blockData.push_back(Block(i + xSize * x, j, k + zSize * z));
				index++;
			}
		}
	}
}


void Chunk::generateBlocksFromFile(std::ifstream &file)
{
	// Check to make sure file is open
	if (file.is_open())
	{
		// Get file size
		std::streampos fileSize;
		file.seekg(0, std::ios::end); // go to end of file
		fileSize = file.tellg(); // read position
		file.seekg(0, std::ios::beg); // reset to beginning of file
		
		// Read into vector
		std::vector<unsigned char> data;
		data.reserve(fileSize);
		data.insert(data.begin(),
				    std::istream_iterator<unsigned char>(file),
				    std::istream_iterator<unsigned char>());
		
		int index = 0;
		
		// Extract "x" integer
		int chunkX = integerFromBytes(data, index);
		index += 4;
		
		// Extract "z" integer
		int chunkZ = integerFromBytes(data, index);
		index += 4;
		
		// Check to make sure we are reading correct chunk, implement this as class func
		// to get access to class variables.
		
		// Extract size
		int size = integerFromBytes(data, index);
		index += 4;
		
		// Get block positions
		for (int i = 0; i < size; i++)
		{
			int x = integerFromBytes(data, index);
			index += 4;
			int y = integerFromBytes(data, index);
			index += 4;
			int z = integerFromBytes(data, index);
			index += 4;
			
			blockData.push_back(Block(x, y, z));
		}
	}
}


void Chunk::loadGPU()
{
	// Update chunk state
	loaded = true;

	// Create VAO on chunk creation
	glGenVertexArrays(1, &VAO);

	// Set up OpenGL buffers
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &textureVBO);
	
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


void Chunk::unloadGPU()
{
	double startTime = glfwGetTime();
	
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
	
	double endTime = glfwGetTime();
	std::cout << "Unloaded chunk " << x << "," << z << " in " << endTime - startTime << std::endl;
}


void Chunk::save()
{
	// Current file format is as follows:
	// - 4-byte integer x, 4-byte integer z, 4-byte integer size (number of blocks)
	//   then the remaining data are the blocks positions in order. (x, y, z) each
	//   a 4-byte integer
	
	std::string filename = "chunks/" + std::to_string(x) + "." + std::to_string(z) + ".chunk";
	
	std::ofstream outFile;
	outFile.open(filename, std::ios::out | std::ios::binary);
	
	// Chunk position
	outFile.write(reinterpret_cast<char*>(&x), sizeof(x));
	outFile.write(reinterpret_cast<char*>(&z), sizeof(z));
	
	// Chunk block data size
	int size = blockData.size();
	outFile.write(reinterpret_cast<char*>(&size), sizeof(size));
	
	// Chunk block data
	for (int i=0; i<size; i++)
	{
		outFile.write(reinterpret_cast<char*>(&blockData[i].x), sizeof(blockData[i].x));
		outFile.write(reinterpret_cast<char*>(&blockData[i].y), sizeof(blockData[i].y));
		outFile.write(reinterpret_cast<char*>(&blockData[i].z), sizeof(blockData[i].z));
	}
	
	outFile.close();
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
	// Out of range means we need to check the neighboring chunks if we want to cull chunk boundaries
	else
	{
		return false;
	}
}


void Chunk::addToVector(std::vector<float>& original, std::vector<float>& itemsToAdd)
{
	for (int i=0; i<itemsToAdd.size(); i++)
	{
		original.push_back(itemsToAdd[i]);
	}
}


void Chunk::mesh()
{
	// Clear data before meshing
	vertices.clear();
	texCoords.clear();
	
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
			addToVector(vertices, faceVerts);
			
			std::vector<float> faceTexCoords = blockData[i].getFrontFaceTexCoords();
			addToVector(texCoords, faceTexCoords);
		}
		// Right face
		if (!findBlock(x+1, y, z))
		{
			std::vector<float> faceVerts = blockData[i].getRightFaceVertices();
			addToVector(vertices, faceVerts);
			
			std::vector<float> faceTexCoords = blockData[i].getRightFaceTexCoords();
			addToVector(texCoords, faceTexCoords);
		}
		// Top face
		if (!findBlock(x, y+1, z))
		{
			std::vector<float> faceVerts = blockData[i].getTopFaceVertices();
			addToVector(vertices, faceVerts);
			
			std::vector<float> faceTexCoords = blockData[i].getTopFaceTexCoords();
			addToVector(texCoords, faceTexCoords);
		}
		// Left face
		if (!findBlock(x-1, y, z))
		{
			std::vector<float> faceVerts = blockData[i].getLeftFaceVertices();
			addToVector(vertices, faceVerts);
			
			std::vector<float> faceTexCoords = blockData[i].getLeftFaceTexCoords();
			addToVector(texCoords, faceTexCoords);
		}
		// Back face
		if (!findBlock(x, y, z-1))
		{
			std::vector<float> faceVerts = blockData[i].getBackFaceVertices();
			addToVector(vertices, faceVerts);
			
			std::vector<float> faceTexCoords = blockData[i].getBackFaceTexCoords();
			addToVector(texCoords, faceTexCoords);
		}
		// Bottom face
		if (!findBlock(x, y-1, z))
		{
			std::vector<float> faceVerts = blockData[i].getBottomFaceVertices();
			addToVector(vertices, faceVerts);
			
			std::vector<float> faceTexCoords = blockData[i].getBottomFaceTexCoords();
			addToVector(texCoords, faceTexCoords);
		}
	}
}


Chunk::Chunk(){};


Chunk::Chunk(int x, int z)
{
    this -> x = x;
    this -> z = z;
	
	double startTime = glfwGetTime();
	
	// Attempt to read chunk contents from file
	std::string filename = "chunks/" + std::to_string(x) + "." + std::to_string(z) + ".chunk";
	std::ifstream chunkFile(filename, std::ios::binary);
	chunkFile.unsetf(std::ios::skipws); // don't eat newlines
	
	if (chunkFile.is_open())
	{
		std::cout << "Found chunk file for chunk " << x << "," << z << std::endl;
		
		generateBlocksFromFile(chunkFile);
		
		chunkFile.close();
	}
	
	else
	{
		generate();
	}
	double genTime = glfwGetTime();

    // Construct mesh on generation
	mesh();
	double meshTime = glfwGetTime();
	
	// Load data into buffers for rendering
	// Assumes that when a chunk is generated it should be ready to render
	loadGPU();
	double loadTime = glfwGetTime();
	
	std::cout << "Generating chunk " << x << "," << z << " took " << genTime-startTime << std::endl;
	std::cout << "Generating mesh for chunk " << x << "," << z << " took " << meshTime-genTime << std::endl;
	std::cout << "Loading chunk " << x << "," << z << " took " << loadTime-meshTime << "\n" << std::endl;
}