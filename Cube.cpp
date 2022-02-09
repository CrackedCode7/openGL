#include "Cube.h"

#include <vector>


Cube::Cube(float x, float y, float z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;

    this -> vertices = {
        0.0f+x, 0.0f+y, 0.0f+z,
        1.0f+x, 0.0f+y, 0.0f+z,
        1.0f+x, 1.0f+y, 0.0f+z,
        0.0f+x, 1.0f+y, 0.0f+z,
        0.0f+x, 0.0f+y, -1.0f+z,
        1.0f+x, 0.0f+y, -1.0f+z,
        1.0f+x, 1.0f+y, -1.0f+z, 
        0.0f+x, 1.0f+y, -1.0f+z
        };

    this -> indices = {
        0, 1, 2, // front
        0, 2, 3, // front
        1, 5, 6, // right
        1, 6, 2, // right
        3, 2, 6, // top
        3, 6, 7, // top
        0, 3, 7, // left
        0, 7, 4, // left
        4, 7, 6, // back
        4, 6, 5, // back
        0, 4, 5, // bottom
        0, 5, 1 // bottom
    };
};