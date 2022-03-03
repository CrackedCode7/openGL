#include "util.h"

#include <string>


float xPixelToScreenCoords(float xPixel, float xScreenSize)
{
	return (xPixel-(xScreenSize/2))/(xScreenSize/2);
}


float yPixelToScreenCoords(float yPixel, float yScreenSize)
{
	return ((yScreenSize/2)-yPixel)/(yScreenSize/2);
}


int positiveModulo(int x, int N)
{
	return (x % N + N) % N;
}


std::vector<unsigned char> integerToChar(int num)
{
	std::vector<unsigned char> bytes;
	
	bytes.push_back((num >> 24) & 0xFF);
	bytes.push_back((num >> 16) & 0xFF);
	bytes.push_back((num >> 8) & 0xFF);
	bytes.push_back(num & 0xFF);
	
	return bytes;
}