#include "text.h"

#include "Texture.h"
#include "twoDimensionalObject.h"
#include <string>


// Constructor takes the input string and location/size info
// A 2D object is made for each character in the string, with the
// correct location in screen space given as input to the 2D objects
// constructor.
// We are using the constant map of the texture to determine the texture 
// pixel locations for the 2D object constructor

Text::Text(std::string text, float xLoc, float yLoc, float xSize, float ySize, float xScreenSize, float yScreenSize, Texture texture)
{
	// Iterate over characters, make and store 2-D objects.
	for (int i=0; i<text.length(); i++)
	{
		std::string letter;
		letter.push_back(text[i]);
		
		objects.push_back(TwoDimensionalObject(xLoc+i*xSize, yLoc, xSize, ySize, xScreenSize, yScreenSize, texture.dict[letter][0], texture.dict[letter][1], texture.dict[letter][2], texture.dict[letter][3], texture));
	}
	
	// Construct vertices, indices, and texCoords from objects
	for (int i=0; i<objects.size(); i++)
	{
		for (int j=0; j<objects[i].vertices.size(); j++)
		{
			vertices.push_back(objects[i].vertices[j]);
		}
		for (int j=0; j<objects[i].texCoords.size(); j++)
		{
			texCoords.push_back(objects[i].texCoords[j]);
		}
		for (int j=0; j<objects[i].indices.size(); j++)
		{
			indices.push_back(objects[i].indices[j]+4*i);
		}
	}
}