#include "twoDimensionalObject.h"
#include "util.h"

#include <string>
#include <iostream>


TwoDimensionalObject::TwoDimensionalObject(float xLoc, float yLoc, float xSize, float ySize, float texPixelX, float texPixelY, float texSizeX, float texSizeY, float xScreenSize, float yScreenSize)
{
    vertices.push_back(xPixelToScreenCoords(xLoc, xScreenSize)); // x0
    vertices.push_back(yPixelToScreenCoords(yLoc+ySize, yScreenSize)); // y0
    vertices.push_back(0.0f); // z0

    vertices.push_back(xPixelToScreenCoords(xLoc+xSize, xScreenSize)); // x1
    vertices.push_back(yPixelToScreenCoords(yLoc+ySize, yScreenSize)); // y1
    vertices.push_back(0.0f); // z1

    vertices.push_back(xPixelToScreenCoords(xLoc+xSize, xScreenSize)); // x2
    vertices.push_back(yPixelToScreenCoords(yLoc, yScreenSize)); // y2
    vertices.push_back(0.0f); // z2

    vertices.push_back(xPixelToScreenCoords(xLoc, xScreenSize)); // x3
    vertices.push_back(yPixelToScreenCoords(yLoc, yScreenSize)); // y3
    vertices.push_back(0.0f); // z3

    
    // 0, 1, 2 first triangle, 0, 2, 3 second triangle
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);


    texCoords.push_back(texPixelX/512); // 0
    texCoords.push_back((512-texPixelY-8)/512); // 0
    texCoords.push_back((texPixelX+8)/512); // 1
    texCoords.push_back((512-texPixelY-8)/512); // 1
    texCoords.push_back((texPixelX+8)/512); // 2
    texCoords.push_back((512-texPixelY)/512); // 2
    texCoords.push_back(texPixelX/512); // 3
    texCoords.push_back((512-texPixelY)/512); // 3
}