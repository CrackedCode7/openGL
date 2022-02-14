#pragma once

#include "twoDimensionalObject.h"
#include "Texture.h"

#include <vector>
#include <string>

// Text should take the text string as input and the starting position of the text object in pixels.
// Then it should use TwoDimensionalObjects for each text character, and place them appropriately and index the atlas.

// text: text string to display
// xLoc: x location in pixels from left of screen to place object at
// yLoc: y location in pixels from top of screen to place object at
// xSize: screen width of the object in pixels, per text character
// ySize: screen height of the object in pixels, per text character
// xScreenSize: width in pixels of the screen
// yScreenSize: height in pixels of the screen
// texture: Texture object storing texture dims and locations of items

class Text
{
	public:
		std::vector<TwoDimensionalObject> objects;
		
		std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;
		
		Text(std::string text, float xLoc, float yLoc, float xSize, float ySize, float xScreenSize, float yScreenSize, Texture texture);
};