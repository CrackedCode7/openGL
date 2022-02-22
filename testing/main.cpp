#include <fstream>
#include <iostream>
#include <string>
#include <map>


int main()
{
	std::map<std::string

	std::ifstream file;
	file.open("config.cfg", std::ios::in);
	
	std::string line;
	std::string delimeter = "=";
	while (file >> line)
	{
		int delimeter_pos = line.find(delimeter);
		std::string parameter = line.substr(0, delimeter_pos);
		std::string value = line.substr(delimeter_pos+1, line.length());
		std::cout << parameter << " : " << value << std::endl;
	}
	
	file.close();
}