#include <iostream>
#include <vector>


void withReserve(int n)
{
	std::vector<int> vec;
	vec.reserve(1000000);
	
	for (int i=0; i<n; i++)
	{
		vec.push_back(i);
	}
}


void withoutReserve(int n)
{
	std::vector<int> vec;
	
	for (int i=0; i<n; i++)
	{
		vec.push_back(i);
	}
}


int main()
{
	std::cout << "With reserve running..." << std::endl;
	withReserve(1000000000);
	std::cout << "Done." << std::endl;
	
	std::cout << "Without reserve running..." << std::endl;
	withoutReserve(1000000000);
	std::cout << "Done." << std::endl;
}