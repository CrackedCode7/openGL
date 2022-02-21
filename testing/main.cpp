#include <fstream>
#include <iostream>
#include <string>


int main()
{
	std::ifstream file;
	file.open("config.cfg", std::ios::in);
	
	std::string line;
	while (file >> line)
	{
		std::cout << line << std::endl;
	}
	
	file.close();
}