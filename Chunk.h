#pragma once

#include "Cube.h"

#include <map>
#include <vector>


class Chunk
{
    public:
        int x;
        int z;
        std::vector<Cube> blockData;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> texCoords;

        Chunk(int x, int y);
};