#include "debugScreen.h"

#include "text.h"
#include <glad/glad.h>
#include <iostream>


DebugScreen::DebugScreen()
{
	// Set up OpenGL buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	
	// Unbind (don't need EBO because it is per VAO, not global state)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void DebugScreen::updateText(Text* fpsText, Text* tpsText)
{
	vertices.clear();
	indices.clear();
	texCoords.clear();
	
	for (int i=0; i<fpsText->vertices.size(); i++)
	{
		vertices.push_back(fpsText->vertices[i]);
	}
	for (int i=0; i<fpsText->indices.size(); i++)
	{
		indices.push_back(fpsText->indices[i]);
	}
	for (int i=0; i<fpsText->texCoords.size(); i++)
	{
		texCoords.push_back(fpsText->texCoords[i]);
	}
	
	for (int i=0; i<tpsText->vertices.size(); i++)
	{
		vertices.push_back(tpsText->vertices[i]);
	}
	for (int i=0; i<tpsText->indices.size(); i++)
	{
		indices.push_back(tpsText->indices[i]+4*fpsText->text.length());
	}
	for (int i=0; i<tpsText->texCoords.size(); i++)
	{
		texCoords.push_back(tpsText->texCoords[i]);
	}

	// Update buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), &texCoords[0], GL_DYNAMIC_DRAW);
	
	// Unbind (don't need EBO because it is per VAO, not global state)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void DebugScreen::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}