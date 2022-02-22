#pragma once

#include "src/textures/Texture.h"
#include <vector>


// xLoc: x location in pixels from left of screen to place object at
// yLoc: y location in pixels from top of screen to place object at
// xSize: width of the object in pixels
// ySize: height of the object in pixels
// texPixelX: x location in pixels from the texture atlas
// texPixelY: y location in pixels from the texture atlas
// texSizeX: width of the texture atlas in pixels
// texSizeY: height of the texture atlas in pixels
// xScreenSize: width in pixels of the screen
// yScreenSize: height in pixels of the screen
class TwoDimensionalObject
{
    public:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;

        TwoDimensionalObject(float xLoc, float yLoc, float xSize, float ySize, float xScreenSize, float yScreenSize, float texPixelX, float texPixelY, float texSizeX, float texSizeY, Texture* texture);
};