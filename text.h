#pragma once

#include <string>
#include <vector>
#include <map>


class Text
{
    public:
        static std::map<char, std::vector<int>> textureMap;

        std::string text;
        size_t length;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;

        Text(float xPos, float yPos, float ySize, std::string text);
};