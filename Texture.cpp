#include "Texture.h"

#include <glad/glad.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "stb_image.h"


// Vector of int is xPos, yPos, xSize, ySize in pixels from texture atlas
std::map<std::string, std::vector<int>> Texture::dict
{
	{"grass_side", std::vector<int> {0, 0, 16, 16}},
	{"grass_top", std::vector<int> {16, 0, 16, 16}},
	{"grass_bottom", std::vector<int> {32, 0, 16, 16}},
	{"A", std::vector<int> {0, 504, 8, 8}},
	{"B", std::vector<int> {8, 504, 8, 8}},
	{"C", std::vector<int> {16, 504, 8, 8}},
	{"D", std::vector<int> {24, 504, 8, 8}},
	{"E", std::vector<int> {32, 504, 8, 8}},
	{"F", std::vector<int> {40, 504, 8, 8}},
	{"G", std::vector<int> {48, 504, 8, 8}},
	{"H", std::vector<int> {56, 504, 8, 8}},
	{"I", std::vector<int> {64, 504, 8, 8}},
	{"J", std::vector<int> {72, 504, 8, 8}},
	{"K", std::vector<int> {80, 504, 8, 8}},
	{"L", std::vector<int> {88, 504, 8, 8}},
	{"M", std::vector<int> {96, 504, 8, 8}},
	{"N", std::vector<int> {104, 504, 8, 8}},
	{"O", std::vector<int> {112, 504, 8, 8}},
	{"P", std::vector<int> {120, 504, 8, 8}},
	{"Q", std::vector<int> {128, 504, 8, 8}},
	{"R", std::vector<int> {136, 504, 8, 8}},
	{"S", std::vector<int> {144, 504, 8, 8}},
	{"T", std::vector<int> {152, 504, 8, 8}},
	{"U", std::vector<int> {160, 504, 8, 8}},
	{"V", std::vector<int> {168, 504, 8, 8}},
	{"W", std::vector<int> {176, 504, 8, 8}},
	{"X", std::vector<int> {184, 504, 8, 8}},
	{"Y", std::vector<int> {192, 504, 8, 8}},
	{"Z", std::vector<int> {200, 504, 8, 8}},
	{"0", std::vector<int> {208, 504, 8, 8}},
	{"1", std::vector<int> {216, 504, 8, 8}},
	{"2", std::vector<int> {224, 504, 8, 8}},
	{"3", std::vector<int> {232, 504, 8, 8}},
	{"4", std::vector<int> {240, 504, 8, 8}},
	{"5", std::vector<int> {248, 504, 8, 8}},
	{"6", std::vector<int> {256, 504, 8, 8}},
	{"7", std::vector<int> {264, 504, 8, 8}},
	{"8", std::vector<int> {272, 504, 8, 8}},
	{"9", std::vector<int> {280, 504, 8, 8}},
};


Texture::Texture(const char* filename)
{
	stbi_set_flip_vertically_on_load(true);
	
	data = stbi_load(filename, &width, &height, &nrChannels, 0);
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set texture wrapping and filter options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); // free image memory
}