#pragma once

#include <map>
#include <vector>
#include <string>

class Texture
{
	public:
		int width;
		int height;
		int nrChannels;
		unsigned char* data;
		unsigned int texture;
		
		static std::map<std::string, std::vector<int>> dict;
		
		Texture();
		Texture(const char* filename);
};