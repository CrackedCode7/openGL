#pragma once

#include <vector>


class Cube
{
    public:

        float x;
        float y;
        float z;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        Cube(float x, float y, float z);
};