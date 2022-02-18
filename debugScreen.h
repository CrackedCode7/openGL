#pragma once

#include <vector>


class DebugScreen
{
    public:

        std::vector<float> vertices;
        std::vector<float> indices;
        std::vector<float> texCoords;

        DebugScreen();
};