#include "util.h"


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