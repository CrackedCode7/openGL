#include "text.h"
#include "util.h"

#include <string>
#include <iostream>


std::map<char, std::vector<float>> Text::textureMap
{
	{'A', std::vector<float> {0.0f, 504.0f}},
	{'B', std::vector<float> {8.0f, 504.0f}},
	{'C', std::vector<float> {16.0f, 504.0f}},
	{'D', std::vector<float> {24.0f, 504.0f}},
	{'E', std::vector<float> {32.0f, 504.0f}},
	{'F', std::vector<float> {40.0f, 504.0f}},
	{'G', std::vector<float> {48.0f, 504.0f}},
	{'H', std::vector<float> {56.0f, 504.0f}},
	{'I', std::vector<float> {64.0f, 504.0f}},
	{'J', std::vector<float> {72.0f, 504.0f}},
	{'K', std::vector<float> {80.0f, 504.0f}},
	{'L', std::vector<float> {88.0f, 504.0f}},
	{'M', std::vector<float> {96.0f, 504.0f}},
	{'N', std::vector<float> {104.0f, 504.0f}},
	{'O', std::vector<float> {112.0f, 504.0f}},
	{'P', std::vector<float> {120.0f, 504.0f}},
	{'Q', std::vector<float> {128.0f, 504.0f}},
	{'R', std::vector<float> {136.0f, 504.0f}},
	{'S', std::vector<float> {144.0f, 504.0f}},
	{'T', std::vector<float> {152.0f, 504.0f}},
	{'U', std::vector<float> {160.0f, 504.0f}},
	{'V', std::vector<float> {168.0f, 504.0f}},
	{'W', std::vector<float> {176.0f, 504.0f}},
	{'X', std::vector<float> {184.0f, 504.0f}},
	{'Y', std::vector<float> {192.0f, 504.0f}},
	{'Z', std::vector<float> {200.0f, 504.0f}},
};


Text::Text(float xLoc, float yLoc, float xSize, float ySize, float xScreenSize, float yScreenSize, std::string text)
{       
    this -> text = text;
    length = text.length();

    for (int i=0; i<length; i++)
    {	
        vertices.push_back(xPixelToScreenCoords(xLoc+xSize*i, xScreenSize)); // x0
        vertices.push_back(yPixelToScreenCoords(yLoc+ySize, yScreenSize)); // y0
        vertices.push_back(0.0f); // z0

        vertices.push_back(xPixelToScreenCoords(xLoc+xSize*i+xSize, xScreenSize)); // x1
        vertices.push_back(yPixelToScreenCoords(yLoc+ySize, yScreenSize)); // y1
        vertices.push_back(0.0f); // z1

        vertices.push_back(xPixelToScreenCoords(xLoc+xSize*i+xSize, xScreenSize)); // x2
        vertices.push_back(yPixelToScreenCoords(yLoc, yScreenSize)); // y2
        vertices.push_back(0.0f); // z2

        vertices.push_back(xPixelToScreenCoords(xLoc+xSize*i, xScreenSize)); // x3
        vertices.push_back(yPixelToScreenCoords(yLoc, yScreenSize)); // y3
        vertices.push_back(0.0f); // z3

		
		// 0, 1, 2 first triangle, 0, 2, 3 second triangle
        indices.push_back(0+4*i);
        indices.push_back(1+4*i);
        indices.push_back(2+4*i);
        indices.push_back(0+4*i);
        indices.push_back(2+4*i);
        indices.push_back(3+4*i);
		
		
		// Depends on texture size 512x512, 8x8 text sprites
        texCoords.push_back(textureMap[text[i]][0]/512); // 0
        texCoords.push_back((512-textureMap[text[i]][1]-8)/512); // 0
        texCoords.push_back((textureMap[text[i]][0]+8)/512); // 1
        texCoords.push_back((512-textureMap[text[i]][1]-8)/512); // 1
        texCoords.push_back((textureMap[text[i]][0]+8)/512); // 2
        texCoords.push_back((512-textureMap[text[i]][1])/512); // 2
		texCoords.push_back(textureMap[text[i]][0]/512); // 3
        texCoords.push_back((512-textureMap[text[i]][1])/512); // 3
    }
}