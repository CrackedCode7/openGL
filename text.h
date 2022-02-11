#pragma once

#include <string>
#include <vector>
#include <map>


class Text
{
    public:
        static std::map<char, std::vector<float>> textureMap;

        std::string text;
        size_t length;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;

        Text(float xLoc, float yLoc, float xSize, float ySize, float xScreenSize, float yScreenSize, std::string text);
};