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


int integerFromBytes(std::vector<unsigned char> &input, int offset)
{
	return int((input[3+offset]) << 24 |
			   (input[2+offset]) << 16 |
			   (input[1+offset]) << 8 |
			   (input[0+offset]));
}