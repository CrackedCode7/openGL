#pragma once

#include <vector>
#include <string>


float xPixelToScreenCoords(float xPixel, float xScreenSize);
float yPixelToScreenCoords(float yPixel, float yScreenSize);

//std::vector<float> texturePixelToTextureCoords(float xPixel, float yPixel, float xSize, float ySize, float xTextureSize, float yTextureSize);

int positiveModulo(int x, int N);

int integerFromBytes(std::vector<unsigned char> &input, int offset);